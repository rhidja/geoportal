<?php

function geoportal_edit_data_category_form($dcid) {
	return drupal_get_form('geoportal_data_category_form',$dcid);
}

function geoportal_add_data_category_form() {
	return drupal_get_form('geoportal_data_category_form');
}

function geoportal_data_category_form($form,&$form_state,$dcid=''){
	
	$form['data_category'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);

	if(!empty($dcid)){
		$query = db_select('geoportal_data_category','c')
		->fields('c')
		->condition('dcid' , $dcid , '=')
		->execute();
		$data_category = $query->fetch();
	}

	$form['data_category']['num'] = array(
		'#type'          => 'hidden',
		'#default_value' => !empty($data_category->num) ? $data_category->num : '',
		'#disabled'      => TRUE,
		);

	$form['data_category']['dcid'] = array(
		'#type'     => 'textfield',
		'#title'    => t('Id'),
		'#required' => TRUE,
		'#default_value' => !empty($data_category->dcid) ? $data_category->dcid : '',
		);
	
	$form['data_category']['status'] = array(
		'#type'     => 'checkbox',
		'#title'    => t('Enable'),
		'#default_value' => !empty($data_category->status) ? $data_category->status : 0,
		);

	$form['data_category']['name'] = array(
		'#type'     => 'textfield',
		'#title'    => t('Name'),
		'#required' => TRUE,
		'#default_value' => !empty($data_category->name) ? $data_category->name : '',
		);

	$form['data_category']['description'] = array(
		'#type'     => 'textarea',
		'#title'    => t('Description'),
		'#default_value' => !empty($data_category->description) ? $data_category->description : '',
		);
	
	$form['data_category']['submit'] = array(
		'#type'     => 'submit',
		'#value'    => !empty($data_category->dcid) ? t('Update') : t('Submit'),
		);	

	return $form;
}

function geoportal_data_category_form_submit($form,&$form_state){

	if(!empty($form_state['values']['num'])){
		db_update('geoportal_data_category')
		->fields(array(
			'dcid'          => $form_state['values']['dcid'],
			'name'         => $form_state['values']['name'],
			'status'       => $form_state['values']['status'],
			'description'  => $form_state['values']['description'],
			))
		->condition('num',$form_state['values']['num'], '=')
		->execute();

		drupal_set_message(t('Le data_categoryue  "@name"  est modifié',
			array(
				'@name' => $form_state['values']['name'],
				)
			));

	}else{
		db_insert('geoportal_data_category')
		->fields(array(
			'dcid'          => $form_state['values']['dcid'],
			'name'         => $form_state['values']['name'],
			'status'       => $form_state['values']['status'],
			'description'  => $form_state['values']['description'],
			))
		->execute();

		drupal_set_message(t('Le data_categoryue  "@name"  est ajouté',
			array(
				'@name' => $form_state['values']['name'],
				)
			));
	}
	$form_state['redirect'] = 'admin/config/geoportal';
}


function geoportal_delete_data_category_form($form,&$form_state,$dcid='') {

	$form['data_category'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);
	$form['data_category']['message1'] = array(
		'#markup' => t('The following data category will be definitely deleted from your site!'),
		);

	$form['data_category']['dcid'] = array(
		'#type' => 'hidden',
		'#title' => t($dcid),
		'#default_value' => !empty($dcid) ? $dcid : '',
		);

	$form['data_category']['message2'] = array(
		'#type' => 'item',
		'#title' => t($dcid),
		'#markup' => t('Would you like to continue with deleting the above?'),
		);

	$form['data_category']['submit'] = array(
		'#type'     => 'submit',
		'#value'    => t('Delete'),
		);

	return $form;
}

function geoportal_delete_data_category_form_submit($form,&$form_state) {

	$dcid = $form_state['values']['dcid'];
	
	db_delete('geoportal_data_category')
	->condition('dcid', $dcid)
	->execute();
	
	drupal_set_message(t('The data_category  "@dcid"  is definitely deleted.',
		array(
			'@dcid' => $form_state['values']['dcid'],
			)
		));
	$form_state['redirect'] = 'admin/config/geoportal';
}