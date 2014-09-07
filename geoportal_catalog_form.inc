<?php

function geoportal_edit_catalog_form($cid) {
	return drupal_get_form('geoportal_catalog_form',$cid);
}

function geoportal_add_catalog_form() {
	return drupal_get_form('geoportal_catalog_form');
}

function geoportal_catalog_form($form,&$form_state,$cid=''){
	
	$form['catalog'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);

	if(!empty($cid)){
		$query = db_select('geoportal_catalogs','c')
		->fields('c')
		->condition('cid' , $cid , '=')
		->execute();
		$catalog = $query->fetch();
	}

	$form['catalog']['num'] = array(
		'#type'          => 'hidden',
		'#default_value' => !empty($catalog->num) ? $catalog->num : '',
		'#disabled'      => TRUE,
		);

	$form['catalog']['cid'] = array(
		'#type'     => 'textfield',
		'#title'    => t('Id'),
		'#required' => TRUE,
		'#default_value' => !empty($catalog->cid) ? $catalog->cid : '',
		);
	
	$form['catalog']['status'] = array(
		'#type'     => 'checkbox',
		'#title'    => t('Enable'),
		'#default_value' => !empty($catalog->status) ? $catalog->status : 0,
		);

	$form['catalog']['name'] = array(
		'#type'     => 'textfield',
		'#title'    => t('Name'),
		'#required' => TRUE,
		'#default_value' => !empty($catalog->name) ? $catalog->name : '',
		);

	$form['catalog']['description'] = array(
		'#type'     => 'textarea',
		'#title'    => t('Description'),
		'#default_value' => !empty($catalog->description) ? $catalog->description : '',
		);
	
	$form['catalog']['submit'] = array(
		'#type'     => 'submit',
		'#value'    => !empty($catalog->cid) ? t('Update') : t('Submit'),
		);	

	return $form;
}

function geoportal_catalog_form_submit($form,&$form_state){

	if(!empty($form_state['values']['num'])){
		db_update('geoportal_catalogs')
		->fields(array(
			'cid'          => $form_state['values']['cid'],
			'name'         => $form_state['values']['name'],
			'status'       => $form_state['values']['status'],
			'description'  => $form_state['values']['description'],
			))
		->condition('num',$form_state['values']['num'], '=')
		->execute();

		drupal_set_message(t('Le catalogue  "@name"  est modifié',
			array(
				'@name' => $form_state['values']['name'],
				)
			));

	}else{
		db_insert('geoportal_catalogs')
		->fields(array(
			'cid'          => $form_state['values']['cid'],
			'name'         => $form_state['values']['name'],
			'status'       => $form_state['values']['status'],
			'description'  => $form_state['values']['description'],
			))
		->execute();

		drupal_set_message(t('Le catalogue  "@name"  est ajouté',
			array(
				'@name' => $form_state['values']['name'],
				)
			));
	}
}


function geoportal_delete_catalog_form($form,&$form_state,$cid='') {

	$form['catalog'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);
	$form['catalog']['message1'] = array(
		'#markup' => t('The following catalog will be definitely deleted from your site!'),
		);

	$form['catalog']['cid'] = array(
		'#type' => 'hidden',
		'#title' => t($cid),
		'#default_value' => !empty($cid) ? $cid : '',
		);

	$form['catalog']['message2'] = array(
		'#type' => 'item',
		'#title' => t($cid),
		'#markup' => t('Would you like to continue with deleting the above?'),
		);

	$form['catalog']['submit'] = array(
		'#type'     => 'submit',
		'#value'    => t('Delete'),
		);

	return $form;
}

function geoportal_delete_catalog_form_submit($form,&$form_state) {

	$cid = $form_state['values']['cid'];
	
	db_delete('geoportal_catalogs')
	->condition('cid', $cid)
	->execute();
	
	drupal_set_message(t('The catalog  "@cid"  is definitely deleted.',
		array(
			'@cid' => $form_state['values']['cid'],
			)
		));
}