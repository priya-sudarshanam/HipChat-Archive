<?php
/**
* This file is for database functions like retrieving, 
* adding data from and to respectively in hipchat table
*/

/**
 * _hipchat_archive_select_data_fordate
 * parameter : $cdate
 * retrieves chata data for a particular date
 * returns chatdata for the selected date
 */
function _hipchat_archive_select_data_fordate($cdate){
    $table = 'hipchat_archive';
    try {
         $selected = db_select('hipchat_archive','hc')
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
 * _hipchat_archive_save_data
 * parameter : $chatValues
 * saves chata data for a particular date
 * returns true if saved, false otherwise
 */
function _hipchat_archive_save_data($chatValues){
  $table = 'hipchat_archive';
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