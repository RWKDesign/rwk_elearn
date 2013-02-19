<?php 

function rwk_user_registration_display(){
  
  global $user;
  $pp_hostname = variable_get('paypal_environment');
  $business_email = variable_get('paypal_business_email', null); 
  
  $subscription_cost = variable_get('user_subscription_cost', null);
  
  
  $domain = $_SERVER['HTTP_HOST'];

  $output = '';
  
  //check to see if current user already has a valid subscription (not yet expired)
  
  $output = 'You must pay in order to register for any of the courses this site has to offer';
  
  $output .= '<span class="course-date-print"> 
  			<h5>If you have questions regarding<br>this service please <a href="" style="color:orange;">Contact Us</a></h5>         
  		  	<form action="https://' . $pp_hostname . '/cgi-bin/webscr" method="post">

			<!-- Identify your business so that you can collect the payments. -->
			<input type="hidden" name="business" value="djanou_1354814897_biz@gmail.com">
			<input type="hidden" name="business" value="'. $business_email .'">
	
			<!-- Internal page where all values will be posted to-->
			<!-- http://acpe.megawan.com/checkout_completed?tx=9T3165212E543803G&st=Completed&amt=0.01&cc=USD&cm=&item_number=ACPE-Bell-Test -->
			<!-- <input type="hidden" name="notify_url" value="http://vc.rwkdesign.com/payment-ipn"> -->
			<input type="hidden" name="notify_url" value="http://' . $domain . '/payment-ipn">

			<!-- Specify a Buy Now button. -->
			<input type="hidden" name="cmd" value="_xclick">

			<!-- Specify details about the item that buyers will purchase. -->
			<input type="hidden" name="item_name" value="User Subscription">
			<input type="hidden" name="amount" value="' . $subscription_cost . '">
			<input type="hidden" name="currency_code" value="USD">

    		<!-- Site specific values to store user and course associations -->
    		<input type="hidden" name="on0" value="user id">
    		<input type="hidden" name="os0" value="' . $user->uid . '">
    		<input type="hidden" name="on1" value="course id">
    		<input type="hidden" name="os1" value="0">

			<!-- Display the payment button. -->
			<input type="image" name="submit" border="0" src="https://www.paypalobjects.com/en_US/i/btn/btn_paynowCC_LG.gif"
			alt="PayPal - The safer, easier way to pay online">
			<img alt="" border="0" width="1" height="1" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" >

  		</form>
  		<br>
  		<h5>If you have questions regarding subscription services<br> please visit our <a href="" style="color:orange;">FAQs</a> or <a href="" style="color:orange;">Contact Us</a></h5>
  		</span>';
        
  
  return $output;
  
}

/**
 * 
 * Implementation of hook_form_alter
 */
function rwk_registration_form_user_register_form_alter(&$form, &$form_state, $form_id){
  
  

  $site_payment_type = variable_get('site_payment_type', null);
  dpm($site_payment_type);
  if($site_payment_type == 'per_user' || $site_payment_type == 'user_and_course'){
    dpm('user needs to pay before creating account');
    $form['#submit'] = array(
    	0 => 'rwk_user_register'
    );
    //$form['#submit'][] = array('user_register_submit');
    
    /*$form['payment'] = array(
      '#type' => 'item',
      '#title' => 'Payment details',
      '#weight' => 10,
      '#markup' => '<form action="https://www.sandbox.paypal.com/cgi-bin/webscr" method="post">

    	<!-- Identify your business so that you can collect the payments. -->
    	<input type="hidden" name="business" value="djanou_1354814897_biz@gmail.com">
    	
    	<!-- Internal page where all values will be posted to-->
    	<!-- http://acpe.megawan.com/checkout_completed?tx=9T3165212E543803G&st=Completed&amt=0.01&cc=USD&cm=&item_number=ACPE-Bell-Test -->
    	<input type="hidden" name="notify_url" value="http://vc.rwkdesign.com/payment-ipn">
    
    	<!-- Specify a Buy Now button. -->
    	<input type="hidden" name="cmd" value="_xclick">
    
    	<!-- Specify details about the item that buyers will purchase. -->
    	<input type="hidden" name="item_name" value="Site Access">
    	<input type="hidden" name="amount" value="10">
    	<input type="hidden" name="currency_code" value="USD">
    
        <!-- Site specific values to store user and course associations -->
        <input type="hidden" name="on0" value="uid">
        <input type="hidden" name="os0" value="0">
        <input type="hidden" name="on1" value="nid">
        <input type="hidden" name="os1" value="0">
    
    	<!-- Display the payment button. -->
    	<input type="image" name="submit" border="0"
    	src="https://www.paypalobjects.com/en_US/i/btn/btn_paynowCC_LG.gif"
    	alt="PayPal - The safer, easier way to pay online">
    	<img alt="" border="0" width="1" height="1"
    	src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" >
    
      </form>',
    );*/
  }
  
  dpm($form);
  dpm($form_state);
  dpm($form_id); 
  
}

function rwk_user_register($form, &$form_state){
  
  dpm('submit function triggered');
  dpm($form);
  dpm($form_state);
  
}
