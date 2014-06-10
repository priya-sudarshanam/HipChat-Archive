<?php
/**
* This file is for database functions like retrieving, 
* adding data from and to respectively in hipchat table
*/

/**
 * Retrieve data from the table('hipchat') for a given date
 */
 function hipchat_select_data_id($cdate){
    $table = 'hipchat';
	try {
         $selected = db_select('hipchat','hc')
	               ->fields('hc')
			       ->condition('cdate',$cdate)
			       ->execute()
			       ->fetchAssoc();
	}
	catch(Exception $e)	{
	     drupal_set_message(t('Issue in retrieving the chat data for date= '.$cdate.'. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
	}
	return $selected;
}
	
/**
 * Insert new chat data values into the table
 */
function hipchat_data($chatValues){
  $table = 'hipchat';
  try {
        $dataInsert = db_insert($table)
	                ->fields(array(
					  'cdate' => $chatValues[0]['cdate'],
					  'cdata' => drupal_json_encode($chatValues[0]['cdata']['messages']),
					   ))
					->execute();
		if ($dataInsert){
		  return true;
		}
     }
  catch(Exception $e) {
        drupal_set_message(t('Adding the new chat data failed. Message = %message, query=%query', 
	    array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return false; 
}