<?php

function geoportal_admin_form($form,&$form_state){
	
	$form['geoportal'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);

	$form['geoportal']['url'] = array(
		'#type' => 'fieldset',
		'#title' => t('Url'),
		'#collapsible' => TRUE,
		'#collapsed'   => FALSE,
		);

	$form['geoportal']['url']['geoportal_url'] = array(
		'#type' => 'textfield',
		'#title' => t('Introduire l\'url de l\'application Geoportal'),
		'#default_value'=> variable_get('geoportal_url',''),
		);

	$form['geoportal']['catalog_add'] = array(
		'#type' => 'link',
		'#title' => t('+ Add catalog'),
		'#href'   => t('admin/config/geoportal/add'),
		);	

	$header_catalogs = array(
		'cid'    => array('data' => t('Id'), 'field' => 'cid'),
		'name'   => t('Name'),
		'status' => t('Status'),
		'edit'   => t('Edit'),
		'delete' => t('Delete'),
		);

	$form['geoportal']['catalogs']  = array(
		'#type' => 'tableselect',
		'#header' => $header_catalogs,
		'#options' => _catalogs_rows($header_catalogs,100),
		'#empty' => t('Table vide.'),
		'#default_value' =>variable_get('catalogs',array()),
		);

	$form['geoportal']['data_category_add'] = array(
		'#type' => 'link',
		'#title' => t('+ Add data category'),
		'#href'   => t('admin/config/geoportal/data_category/add'),
		);	
	$header_category = array(
		'dcid'    => array('data' => t('Id'), 'field' => 'dcid'),
		'name'   => t('Name'),
		'status' => t('Status'),
		'edit'   => t('Edit'),
		'delete' => t('Delete'),
		);

	$form['geoportal']['data_category']  = array(
		'#type' => 'tableselect',
		'#header' => $header_category,
		'#options' => _data_category_rows($header_category,100),
		'#empty' => t('Table vide.'),
		'#default_value' =>variable_get('data_category',array()),
		);	

	return system_settings_form($form);
}


function _catalogs_rows($header,$limit){

	$query =db_select('geoportal_catalogs', 'c')->extend('PagerDefault');
	$query->fields('c');
	$query->extend('TableSort')
	->limit($limit)
	->orderByHeader($header);
	$results = $query->execute();

	$rows = array();
	foreach ($results as $result) {
		$rows[$result->cid] = array(
			'cid'     => t($result->cid),
			'name'    => t($result->name),
			'status'  => ($result->status==1) ? 'Enabled' : 'Disabled',
			'edit'    => array(
				'data' => array(
					'#type'  => 'link',
					'#title' => t('Edit'),
					'#href'  => t('admin/config/geoportal/edit/'.$result->cid),
					),
				),
			'delete'   => array(
				'data' => array(
					'#type'  => 'link',
					'#title' => t('Delete'),
					'#href'  => t('admin/config/geoportal/delete/'.$result->cid),
					),
				),			
			);
	}
	return $rows;
}

function _data_category_rows($header,$limit){

	$query =db_select('geoportal_data_category', 'd')->extend('PagerDefault');
	$query->fields('d');
	$query->extend('TableSort')
	->limit($limit)
	->orderByHeader($header);
	$results = $query->execute();

	$rows = array();
	foreach ($results as $result) {
		$rows[$result->dcid] = array(
			'dcid'     => t($result->dcid),
			'name'    => t($result->name),
			'status'  => ($result->status==1) ? 'Enabled' : 'Disabled',
			'edit'    => array(
				'data' => array(
					'#type'  => 'link',
					'#title' => t('Edit'),
					'#href'  => t('admin/config/geoportal/data_category/edit/'.$result->dcid),
					),
				),
			'delete'   => array(
				'data' => array(
					'#type'  => 'link',
					'#title' => t('Delete'),
					'#href'  => t('admin/config/geoportal/data_category/delete/'.$result->dcid),
					),
				),			
			);
	}
	return $rows;
}