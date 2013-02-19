<?php 

/**
 * 
 * Store Paypal Configuration options for payment transactions
 * hook_admin()
 */
function rwk_registration_admin() {
 
  $form = array();
  
  $form['site_payment_type'] = array(
      '#type' => 'radios',
      '#title' => t('Type of access for payment collections'),
      '#description' => t('Determine when payment will be collected for premium content, for user at time of sign up or per course at time of course registration<br>
      <i>Note that course enrollment costs are set on the course specific configuration page</i>'),
  	  '#required' => TRUE,
      '#options' => array(
          'per_user' => t('Per User'),
          'per_course' => t('Per Course'),
          'user_and_course' => t('Per User and Course'),
      ),
      '#default_value' => variable_get('site_payment_type', null),
  );
  
  $form['user_subscription_cost'] = array(
      '#type' => 'textfield',
      '#title' => 'User Subscription Cost',
      '#size' => 5,
      '#description' => 'The cost per user to gain access to the site and all course content',
      '#default_value' => variable_get('user_subscription_cost', null),
      '#states' => array(
          'visible' => array(
        	':input[name="site_payment_type"]' => array(
                array('value' => t('per_user')),
                array('value' => t('user_and_course'))
            ),
         ),      
      ),
  );
  
  $form['user_subscription_length'] = array(
    '#type' => 'radios',
      '#title' => t('User Subscription Length'),
      '#description' => 'The length of time a user will have access to the site content with a paid subscription before they will be forced to renew',
      '#options' => array(
          'one_week' => t('One Week'),
          'one_month' => t('One Month'),
          'three_months' => t('Three Months'),
          'one_year' => t('One Year'),
          'lifetime' => t('Lifetime Access'),
      ),
      '#default_value' => variable_get('user_subscription_length', null),
      '#states' => array(
          'visible' => array(
        	':input[name="site_payment_type"]' => array(
                array('value' => t('per_user')),
                array('value' => t('user_and_course'))
            ),
         ),      
      ),
  );
  
  $form['course_access_length'] = array(
    '#type' => 'radios',
      '#title' => t('Course Access Length'),
      '#description' => 'The length of time a user will have access to course specific content with a paid enrollment before they will be forced to renew',
      '#options' => array(
          'one_week' => t('One Week'),
          'one_month' => t('One Month'),
          'three_months' => t('Three Months'),
          'one_year' => t('One Year'),
          'lifetime' => t('Lifetime Access'),
      ),
      '#default_value' => variable_get('course_access_length', null),
      '#states' => array(
          'visible' => array(
        	':input[name="site_payment_type"]' => array(
                array('value' => t('per_course')),
                array('value' => t('user_and_course'))
            ),
         ),      
      ),
  );
  
  $form['paypal_environment'] = array(
      '#type' => 'radios',
      '#title' => t('Paypal environment'),
  	  '#required' => TRUE,
      '#options' => array(
          'www.paypal.com' => t('Live'),
          'www.sandbox.paypal.com' => t('Sandbox'),
      ),
      '#default_value' => variable_get('paypal_environment', null),
  );
 
  $form['paypal_pdt_token'] = array(
    '#type' => 'textfield',
    '#size' => 105,
    '#title' => t('Paypal PDT Identity token'),
    '#description' => t('Payment Data Transfer identification token for Paypal transactions.  See <a href="https://www.paypal.com/pdt">PayPal PDT</a> for more details.'),
    '#default_value' => variable_get('paypal_pdt_token', null),    
    '#required' => TRUE,
  );
  
  $form['paypal_business_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Paypal Business Email'),
    '#description' => t('Email used to identify your business so that you can collect the payments.'),
    '#default_value' => variable_get('paypal_business_email', null),    
    '#required' => TRUE,
  );
 
  /*$form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );*/
  
  return system_settings_form($form);
 
}

function rwk_registration_admin_validate($form, &$form_state) {
  
  //dpm($form);
  //dpm($form['site_payment_type']['#value']);
   
  if(($form['site_payment_type']['#value'] == 'per_user' ||  $form['site_payment_type']['#value'] == 'user_and_course') && empty($form['user_subscription_cost']['#value'])) 
    form_set_error('user_subscription_cost', t('User subscription cost is not set.')); 
    
  if(!empty($form['user_subscription_cost']['#value']) && !is_numeric($form['user_subscription_cost']['#value']))
    form_set_error('user_subscription_cost', t('User subscription cost must be an integer.'));  
    
  if(($form['site_payment_type']['#value'] == 'per_user' ||  $form['site_payment_type']['#value'] == 'user_and_course') && empty($form['user_subscription_length']['#value'])) 
    form_set_error('user_subscription_length', t('User subscription length is not set.'));  
    
  if(($form['site_payment_type']['#value'] == 'per_course' ||  $form['site_payment_type']['#value'] == 'user_and_course') && empty($form['course_access_length']['#value'])) 
    form_set_error('course_access_length', t('Course access length is not set.'));   
}

/*function _payment_tracking_set_paypal_form_submit(&$form_state) {
 
  if (isset($form_state['values']['paypal_environment'])) {
    
    switch($form_state['values']['paypal_environment']){
      case 'Live':  
        $env_value = 'www.paypal.com';
        break;      
      case 'Sandbox': 
        $env_value = 'www.sandbox.paypal.com';
        break;      
      default: 
        $env_value = 'www.sandbox.paypal.com';
        break;      
    }
    variable_set('payment_tracking_environment', $env_value);
   
    drupal_set_message(t('Your configuration has been saved.'));
  }
  
  if (intval($form_state['values']['paypal_pdt_token'])) {
    variable_set('payment_tracking_pdt_token', intval($form_state['values']['paypal_pdt_token']));
   
    drupal_set_message(t('Your configuration has been saved.'));
  }
 
}*/

