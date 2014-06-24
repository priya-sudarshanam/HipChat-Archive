<?php
/*
* This file is for database functions like retrieving, 
* adding data from and to, etc respectively in hipchat table 
*/

/*
* Define Constants required for table and alias
*/
define('HIPCHAT_ARCHIVE_TABLE', 'hipchat_archive');
define('HIPCHAT_ARCHIVE_ALIAS', 'ha');


/**
 * _hipchat_archive_select_data_fordate
 * parameter : $cdate
 * retrieves chat data for a particular date
 */
function _hipchat_archive_select_data_fordate($cdate){
    try {
         $cSelected = db_select(HIPCHAT_ARCHIVE_TABLE,HIPCHAT_ARCHIVE_ALIAS)
                   ->fields(ALIAS)
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
 * retrieves time for a particular date
 */
function _hipchat_archive_select_time_fordate($cdate){
    try {
         $cSelected = db_select(HIPCHAT_ARCHIVE_TABLE,HIPCHAT_ARCHIVE_ALIAS)
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
 * saves chat data for a particular date
 * returns true if saved, false otherwise
 */
function _hipchat_archive_save_data($chatValues){
  $cDate = $chatValues[0]['cdate'];
  $cTime = date("H:i:s");
  $cdata = drupal_json_encode($chatValues[0]['cdata']['messages']);
  try {
        $cInserted = db_insert(HIPCHAT_ARCHIVE_TABLE)
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
 $cTime = date("H:i:s");
 $cData = drupal_json_encode($data[0]['cdata']['messages']);
 try {
       $cUpdated = db_update(HIPCHAT_ARCHIVE_TABLE)
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

/**
 * hipchat_archive_checkifexists
 * parameter : $date
 * checks if the given date exists in the db
 * return true or false
 */
function _hipchat_archive_checkifexists($date){
 $exists = false;

 try {
       $exists = db_query('SELECT 1 FROM '.HIPCHAT_ARCHIVE_TABLE.' WHERE cdate = :cdate', array(':cdate' => $date))->fetchField();
  }
  catch (Exception $e){
       drupal_set_message(t('Data not found in the db for the date= '.$date.'. Message = %message, query=%query', 
             array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');
  }
  return $exists; 
}
