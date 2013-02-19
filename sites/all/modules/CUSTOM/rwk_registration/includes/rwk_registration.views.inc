<?php 

/**
 *  Implementation of hook_views_api().
 */
function rwk_registration_views_api() {
  return array(
    'api' => 3,
    'path' => drupal_get_path('module', 'rwk_registration'),    
  );
}

function rwk_registration_views_data(){
  
  $data = array();
  
  // Expose course schema to views.
  module_load_install('rwk_registration');
  
  $data['transactions']['table']['base'] = array(
        'field' => 'tid',
        'title' => 'Paypal Transactions',
        'help' => t('Paypal transactions'),
  );
  
  $data['transactions']['table']['group'] = t('Transactions');
  
  $data['transactions']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  
  $data['transactions']['nid'] = array(
    'title' => 'Node ID of transaction',
  	'help' => t('Node to which the transaction belongs to'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click_sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'title' => 'Course node',
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Purchased node'),
    ),
  );

  $data['transactions']['uid'] = array(
    'title' => 'User ID of transaction',
  	'help' => t('User who performed the transaction'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click_sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user',
    ),
    'relationship' => array(
      'title' => 'User',
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Transaction user'),
    ),
  );
  
  $data['transactions']['payment_date'] = array(
    'title' => t('Date of transaction'),
    'help' => t('The date the user performed the transaction.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  $data['transactions']['payment_expiration'] = array(
    'title' => t('Expiration Date of transaction'),
    'help' => t('The date the transaction is set to expire.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
  
  $data['transactions']['txn_id'] = array(
    'title' => t('Transaction Id'),
    'help' => t('Paypal Transaction Id.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['payment_status'] = array(
    'title' => t('Transaction Status'),
    'help' => t('Paypal Transaction Status.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['item_number'] = array(
    'title' => t('Item Number'),
    'help' => t('Item Number.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['item_name'] = array(
    'title' => t('Item Name'),
    'help' => t('Item Name.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['amt'] = array(
    'title' => t('Amount'),
    'help' => t('Transaction amount.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['currency'] = array(
    'title' => t('Currency'),
    'help' => t('Transaction Currency'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['payment_type'] = array(
    'title' => t('Payment Type'),
    'help' => t('Transaction Payment Type'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['payer_id'] = array(
    'title' => t('Paypal Customer Id'),
    'help' => t('Paypal customer account id'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['transactions']['payer_email'] = array(
    'title' => t('Paypal Customer Email'),
    'help' => t('Paypal customer account email'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['transactions']['tid'] = array(
    'title' => t('Transaction ID'),
    'help' => t('The ID of the transaction.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  
  return $data;
  
}