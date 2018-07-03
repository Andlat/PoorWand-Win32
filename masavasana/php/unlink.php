<?php
//TODO Check session
if(true/*session_ok*/){
  if(!empty($_POST['file'])){
    require_once('file_vars.php');
    if(!unlink($media_dir.$_POST['file']))
    echo "Failed unlinking " . $_POST['file'];
  }
}
?>
