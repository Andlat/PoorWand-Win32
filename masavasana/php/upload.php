<?php
//TODO Check session
if(true/*session_ok*/){
  if (!empty($_FILES)) {
    require_once('file_vars.php');
    if(!move_uploaded_file($_FILES['file']['tmp_name'], $media_dir.$_FILES['file']['name']))
    echo "Failed uploading " . $_FILES['file']['name'];
  }
}
?>
