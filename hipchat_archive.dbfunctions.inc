<?php
/**
* This file is for database functions like retrieving, 
* adding data from and to respectively in hipchat table
*/

/**
 * _hipchat_archive_select_data_fordate
 * parameter : $cdate
 * retrieves chat data for a particular date
 * returns chatdata for the selected date
 */
function _hipchat_archive_select_data_fordate($cdate){
    $table = 'hipchat_archive';
    $tableAlias = 'ha';
    try {
         $cSelected = db_select($table,$tableAlias)
                   ->fields($tableAlias)
                   ->condition('cdate',$cdate)
                   ->execute()
                   ->fetchAssoc();
     }
    catch(Exception $e)	{
             drupal_set_message(t('Issue in retrieving the chat data for date= '.$cdate.'. Message = %message, query=%query', 
             array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
    }
    return $cSelected;
}

/**
 * _hipchat_archive_select_time_fordate
 * parameter : $cdate
 * retrieves chata data for a particular date
 * returns chatdata for the selected date
 */
function _hipchat_archive_select_time_fordate($cdate){
    $table = 'hipchat_archive';
    $tableAlias = 'ha';
    try {
         $cSelected = db_select($table,$tableAlias)
                   ->fields($tableAlias,array('ctime'))
                   ->condition('cdate',$cdate)
                   ->execute()
                   ->fetchAssoc();
     }
    catch(Exception $e)	{
             drupal_set_message(t('Issue in retrieving time for the selected date= '.$cdate.'. Message = %message, query=%query', 
             array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
    }
    return $cSelected;
}


/**
 * _hipchat_archive_save_data
 * parameter : $chatValues
 * saves chata data for a particular date
 * returns true if saved, false otherwise
 */
function _hipchat_archive_save_data($chatValues){
  $table = 'hipchat_archive';
  $cDate = $chatValues[0]['cdate'];
  $cTime = date("H:i:s");
  $cdata = drupal_json_encode($chatValues[0]['cdata']['messages']);
  try {
        $cInserted = db_insert($table)
                     ->fields(array(
                      'cdate' => $cDate,
                      'ctime' =>  $cTime,
                      'cdata' => $cdata,
                      ))
                     ->execute();
      }
  catch(Exception $e) {
        drupal_set_message(t('Adding new chat data failed. Message = %message, query=%query', 
           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $cInserted; 
}

/**
 * _hipchat_archive_update_data
 * parameter : $date,$data
 * updates chat data for a particular date
 * returns true if updated, false otherwise
 */
function _hipchat_archive_update_data($date,$data){
 $table = 'hipchat_archive';
 $cTime = date("H:i:s");
 $cData = drupal_json_encode($data[0]['cdata']['messages']);
 try {
       $cUpdated = db_update($table)
                     ->fields(array(
                        'ctime' => $cTime,
                        'cdata' => $cData,
                        ))
                    ->condition('cdate',$date)
                    ->execute();  
  }
  catch (Exception $e){
       drupal_set_message(t('Issue in updating the chat data for date= '.$date.'. Message = %message, query=%query', 
             array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $cUpdated; 
}
