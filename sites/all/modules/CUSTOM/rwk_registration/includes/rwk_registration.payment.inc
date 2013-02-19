<?php 

function paypal_process_transaction($count = 0){
  
  //used to store the outcome of the transaction and display to the user
  $transaction_message = '';
  $success = FALSE;
  
  //If first attempt to verify against Paypal is unsuccessful, try one more time
  if($count <= 1){
    $hostname = gethostbyaddr($_SERVER['REMOTE_ADDR']);
    
    //Paypal provided sample code
    //$pp_hostname = "www.sandbox.paypal.com"; // Change to www.sandbox.paypal.com to test against sandbox 
    if(isset(variable_get('paypal_environment')))
      $pp_hostname = variable_get('paypal_environment');  
     
    // read the post from PayPal system and add 'cmd'
    $req = 'cmd=_notify-synch';
     
    $tx_token = $_GET['tx'];
    if(isset(variable_get('paypal_pdt_token')))
      $auth_token = variable_get('paypal_pdt_token'); 
    //$auth_token = "gZAXCoCH4-O2KAcJ2MvSRzuHIm7b4QnMOU0bJw8s8kcCAZSKP6J0irX6rXC";  //djanousek@gmail.com sandbox paypal auth token
    $req .= "&tx=$tx_token&at=$auth_token";
     
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, "https://$pp_hostname/cgi-bin/webscr");
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $req);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 1);
    //set cacert.pem verisign certificate path in curl using 'CURLOPT_CAINFO' field here,
    //if your server does not bundled with default verisign certificates.
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 2);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array("Host: $pp_hostname"));
    $res = curl_exec($ch);
    curl_close($ch);
     
    if(!$res){
        //attempt to process again
        paypal_process_transaction($count++);
        print 'Unsuccessful transaction attempt.';
        $transaction_message = '';
    }else{
         print_r($res, TRUE);
         $success = TRUE;
         // parse the data
        $lines = explode("\n", $res);
        $keyarray = array();
        if (strcmp ($lines[0], "SUCCESS") == 0) {
            for ($i=1; $i<count($lines);$i++){
            list($key,$val) = explode("=", $lines[$i]);
            $keyarray[urldecode($key)] = urldecode($val);
        }
        // check the payment_status is Completed
        // check that txn_id has not been previously processed
        // check that receiver_email is your Primary PayPal email
        // check that payment_amount/payment_currency are correct
        // process payment
        
        if($keyarray['option_selection2'] == 0){
          $payment_type = 'Subscription';
          $expiration_value = variable_get('user_subscription_length');
        }else{ 
          $payment_type = 'Enrollment';
          $expiration_value = variable_get('course_access_length');
        }  
                
        //Figure out the payment expiration based upon the sitewide setting
        switch($expiration_value) {
          case 'one_week' : 
            $payment_expiration = mktime(0, 0, 0, date("m"),   date("d")+1,   date("Y")); 
            break;                            
          case 'one_month' :
            $payment_expiration = mktime(0, 0, 0, date("m")+1,   date("d"),   date("Y"));
            break;
          case 'three_months' :
            $payment_expiration = mktime(0, 0, 0, date("m")+3,   date("d"),   date("Y"));
            break;
          case 'one_year' :
            $payment_expiration = mktime(0, 0, 0, date("m"),   date("d"),   date("Y")+1);
            break;
          case 'lifetime' :
            $payment_expiration = mktime(0, 0, 0, date("m"),   date("d"),   date("Y")+1000);
            break;                        
        }  
          
        //store the necessary values into the transactions table
        $tid = db_insert('transactions')
        ->fields(array(
          	'txn_id' => $keyarray['txn_id'],
        	'payment_status' => $keyarray['payment_status'],
        	'item_name' => $keyarray['item_name'],
        	'item_number' => $keyarray['item_number'],
         	'currency' => $keyarray['mc_currency'],
        	'amt' => $keyarray['mc_gross'],
        	'uid' => $keyarray['option_selection1'],
          	'nid' => $keyarray['option_selection2'],      
        	//'payment_date' => $keyarray['payment_date'],
        	'payment_date' => date('Y-m-d H:i:s'),
        	'payment_type' => $payment_type,
          	'payer_id' => $keyarray['option_selection1'],
           	'payer_email' => $keyarray['option_selection2'],
          	'quantity' => $keyarray['quantity'],        
          	'payment_expiration' => $payment_expiration,
        ))
        ->execute();        
        
        $firstname = $keyarray['first_name'];
        $lastname = $keyarray['last_name'];
        $itemname = $keyarray['item_name'];
        $amount = $keyarray['payment_gross'];
     
        $transaction_message = '<p><h3>Thank you for your purchase!</h3></p>';
        $transaction_message .= '<b>Payment Details</b><br>\n';
        $transaction_message .= '<li>Name: $firstname $lastname</li>\n';
        $transaction_message .= '<li>Item: $itemname</li>\n';
        $transaction_message .= '<li>Amount: $amount</li>\n';
        $transaction_message .= '';
        
        /*echo ("<p><h3>Thank you for your purchase!</h3></p>");     
        echo ("<b>Payment Details</b><br>\n");
        echo ("<li>Name: $firstname $lastname</li>\n");
        echo ("<li>Item: $itemname</li>\n");
        echo ("<li>Amount: $amount</li>\n");        
        echo ("");*/
        
        }
        else if (strcmp ($lines[0], "FAIL") == 0) {
            echo("FAIL for strcmp $lines[0]");
        }
    }
  }
  else {
    $transaction_message = '<p>Your Paypal transaction could not be processed succesfully.  Please verify the transaction has cleared within your Paypal account.</p>';
  }
  
  
  $to = "djanousek@gmail.com";
  $subject = "PayPal_IPN Received";
  $body = 'IPN Received from ' . $hostname . "\n\n" . 'POST DATA: ' . print_r($_POST, true) . "\n\n" . 'GET DATA: ' . print_r($_GET, true) . 'res values ' . $res;
  $headers = "";
  //$params = "-f Hit@ACPE_PayPal_IPN.com";
  $params = "";
   
  mail($to, $subject, $body, $headers, $params);
  
  drupal_set_message($transaction_message);
  if($success)
    drupal_goto('node/' . $keyarray['option_selection2'] . '/takecourse');
  else
    drupal_goto('user');
}