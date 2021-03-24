<?php
/**
 * Crea formulario de adminitración
 * Usa variables temporales para guardar información
 * Implements hook_form()
 * @see structureAdmin_menu()
 */
function structureAdmin_admin() {
  $form = [];

  // Se cargan valores de variables temporales
  // Las variables son globales y deberán tener un nombre único
  // Estas deberán ser desinstaladas usando el archivo .install
  $banner_title = variable_get('banner_title','');
  $banner_body  = variable_get('banner_body','');

  // FORM - BANNER
  $form['banner'] = [
    '#type'        => 'fieldset',
    '#title'       => 'CONFIGURACIÓN | BANNER HOME',
    '#weight'      => 1,
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  ];
  $form['banner']['title'] = [
    '#type'          => 'text_format',
    '#title'         => 'Título',
    '#description'   => 'Título de banner.',
    '#default_value' => !empty($banner_title) ? $banner_title['value'] : '',
    '#rows'          => 1,
    '#format'        => 'plain_text',
  ];
  $form['banner']['body'] = [
    '#type'          => 'text_format',
    '#title'         => 'Body',
    '#description'   => 'Descripción de Banner.',
    '#default_value' => !empty($banner_body) ? $banner_body['value'] : '',
    '#rows'          => 3,
    '#format'        => 'plain_text',
  ];
  $form['banner']['img'] = [
    '#type'              => 'managed_file',
    '#title'             => 'Imagen de Banner',
    '#required'          => TRUE,
    '#upload_location'   => file_default_scheme() . '://module/structureAdmin',
    '#default_value'     => variable_get('banner_image', ''),
    '#upload_validators' => [
      'file_validate_extensions' => array('png jpg jpeg'),
    ],
  ];

  // Guardado de forma permanente en archivos
  // Drupal depura los archivos de variables temporales
  //  por lo cual es necesario guardarlos de forma permanente
  $files['module'] = 'structureAdmin';
  $files['files']  = ['banner_image'];
  $status          = structureAdmin_permanentFile($files);
  // Finalizada la carga, genera el formulario con sus métodos de envío
  if ($status === TRUE) {
    return system_settings_form($form);
  }
}

/**
 * Cambia el status a permanente de los archivos temporales
 * @param array $files
 *   $files['module'] => String con el nombre del module
 *   $files['files']  => Array con los nombres de las variables temporales
 * @return boolean
 */
function structureAdmin_permanentFile($files) {
  $status = FALSE;

  try {
    foreach ($admin['files'] as $file) {
      $fid = variable_get($file, '');
      if (isset($fid) && !empty($fid)) {
        $file = file_load($fid);
        if ($file->status == 0) {
          $file->status = FILE_STATUS_PERMANENT;
          file_save($file);
          file_usage_add($file, $admin['module'], $admin['module'], 1);
        }//end if
      }//end if
    }//end foreach
    $status = TRUE;
  } catch ( Exception $e){
    $error = $e->getMessage;
    watchdog('Admin Permanent Files ', 'Error message :%message', array('%message' => $error) );
  }//end try

  return $status;
}
