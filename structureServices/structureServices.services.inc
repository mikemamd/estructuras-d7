<?php
/**
 * @File Libreria de Servicios
 * @author Miguel Martínez <miguel01amd@gmail.com>
 * @package BUPA - Redesign V2
 * @info Este módulo contiene la estrucutra básica para un consumo de servicios
 * @vertion dev 1.0.0.0
 */

/**
 * ESTE MÓDULO NECESITA DE LA INSTALACIÓN PREVIA DE
 * MODULO "SERVICES 3.x" Y SU CONFIGURACIÓN
 */

 /**
  * Función para declarar el servicio
  * Implement hook_services_resources().
  * @see module Services
  */
 function structureServices_services_resources(){
   $resource = array(
     'articles' => array(
       'operations' => array(
         'index' => array(
           'help'             => 'Listado y filtrado de Artículos',
           'callback'         => 'structureServices_servContent',
           'access callback'  => 'structureServices_permission',
           'access arguments' => array('estructuras serv'),
           'access arguments append' => TRUE,
           'args' => array(
             array(
               'name'        => 'filters',
               'type'        => 'array',
               'description' => '',
               'source'      => array('param' => 'filters'),
               'optional'    => TRUE,
               'default'     => [],
             ),
             array(
               'name'        => 'page',
               'type'        => 'int',
               'description' => '',
               'source'      => array('param' => 'page'),
               'optional'    => TRUE,
               'default'     => 1,
             ),
           ),
         ), // end index
       ), // end operations
     ), // end latest
   );

   return $resource;
 }

 /**
  * Se validan los parametros para recibir solo enteros
  * @see structureServices_servContent
  * @param array ($filters)
  * @return boolean ($validate)
  */
 function structureServices_validate($filters) {
   $success = TRUE;

   if ( $filters === NULL ) {
     return $success;
   } // endif

   foreach ($filters[0] as $param => $filter) {
     foreach ($filter as $value) {
       if ( !is_numeric($value) ) {
         $success = FALSE;
         return $success;
       } // endif
     }// endforeach

   }// endforeach

   return $success;
 }

 /**
  * Callback para retornar contnido del servicio
  * @see structureServices_services_resources, structureServices_block_view
  * @param array ($filters) params on service request
  * @return object ($response) data to content of call
  */
 function structureServices_servContent($filters = NULL) {
   $content  = $results = [];
   $response = new stdClass();

   // Se decodifican los parametros en el JSON devuelto
   $filters = json_decode($filters[0], true);

   // Se validan filtros
   $validate = structureServices_validate($filters);

   // Se ejecutan operaciones necesarias en caso de pasar la validación
   if ($validate === TRUE) {
     /*
     $qry = db_select('node', 'n');
     $qry->leftJoin('field_data_body', 'body', 'body.entity_id = n.nid');
     $qry->leftJoin('field_data_field_imgblog', 'img', 'img.entity_id = n.nid');
     $qry->condition('n.type', 'blog_content');
     $qry->condition('n.status', 1);
     $qry->fields('n', ['nid', 'title'])
         ->fields('body', ['body_value'])
         ->fields('img', ['field_imgblog_fid']);
     $qry->orderBy('n.changed', 'ASC');
     $results = $qry->execute()->fetchAll();
     */

     if ( !empty($results)) {
       /*
       // Se recorre arreglo con resultados de la consulta
       foreach ($results as $node) {
         // Se ordena array con el contenido
         $content[$node->nid] = [
           'title' => $node->title,
           'desc'  => $node->body_value,
           'img'   => structureBlock_getimg($node->field_imgblog_fid),
         ];
       } // endforeach
       */

       $response->filters = json_encode($filters);
       $response->success = TRUE;
       $response->message = "success";
       $response->data    = $content;


     } else {
         $response->success = TRUE;
         $response->message = "error";
         $response->data    = [];
     }// endif

   } //endif

   return $response;
 }
