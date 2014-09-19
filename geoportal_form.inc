<?php
// 

/*
 * Dans ce fichier se trouve 6 fonctions :
 *
 * 1. geoportal_recherche_form($form,&$form_state)
 * 2. geoportal_recherche_form_ajax($form, &$form_state)
 * 3. geoportal_recherche_callback($form, &$form_state)
 * 4. catalogues_rows()
 * 5. content_type_rows()
 * 6. data_category_rows()
 *
 */

/*
 * 1. geoportal_recherche_form($form,&$form_status) implémente le la fonction 
 *    hook_form() qui permet la création des formulaire sous drupal.
 *    Ici je l'ai utilisé pour la création du formulaire de recherche de métadonnées.
 *    Les paramètres $form et $form_state sont des paramètres de base de la fonction
 *    hook_form().
 */
function geoportal_recherche_form($form,&$form_state){

	$form['left_bar'] = array(
		'#type'        => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		'#attributes'  => array('class' => array('col-md-5')),
		);

	$form['left_bar']['fieldset_catalogues'] = array(
		'#type' => 'fieldset',
		'#title' => t('Catalogues'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	// Liste des catalogues.
	$form['left_bar']['fieldset_catalogues']['catalogues'] = array( 
		'#type' => 'checkboxes',
		//'#type' => 'radios',
		'#options' => catalogues_rows(),
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),	
		'#suffix' => t('<p><br>* : Catalogues distants.</p>'),
		);

	
	$form['left_bar']['fieldset_data_category'] = array(
		'#type' => 'fieldset',
		'#title' => t('Data Category'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	// Categories de données.
	$form['left_bar']['fieldset_data_category']['data_category'] = array(
		'#type' => 'checkboxes',
		'#options' => data_category_rows(),
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),		
		);

	// Nombre de données
	$form['left_bar']['fieldset_interval_nbre'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	// La donnée de départ.
	$form['left_bar']['fieldset_interval_nbre']['start'] = array(
		'#type' => 'textfield',
		'#title' => t('La donnée de départ'),
		'#size' => 20,
		'#prefix'=>'<table><tr><td>',
		'#suffix'=>'</td><td>',
		);	

	// Le nombre de données
	$form['left_bar']['fieldset_interval_nbre']['max'] = array(
		'#type' => 'textfield',
		'#title' => t('Nombre de données'),
		'#size' => 20,
		'#suffix'=>'</td></tr></table>',
		);

	$form['left_bar']['plus'] = array(
		'#type' => 'fieldset',
		'#title' => t('Plus de filtres...'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		);

	// Ordonner par
	$form['left_bar']['plus']['orderby'] = array(
		'#type' => 'select',
		'#title' => t('Ordonner par'),
		'#default_value'=> 'relevance',
		'#options' => array(
			'relevance'      => 'Pertinence',
			'title'          => 'Titre',
			'format'         => 'Format',
			'dateDescending' => 'De la plus récente à la plus ancienne',
			'dateAscending'  => 'De la plus ancienne à la plus récente',
			'areaAscending'  => 'areaAscending',
			'areaDescending' => 'areaDescending',
			),
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),		
		);

	// Content type
	$form['left_bar']['plus']['content_type'] = array(
		'#type'    => 'select',
		'#title'   => t('Content type'),
		'#options' => content_type_rows(),
		'#default_value'           =>'downloadableData',
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),		
		);
	
	// Période
	$form['left_bar']['plus']['fieldset_periode'] = array(
		'#type' => 'fieldset',
		'#title'   => t('Période'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	$form['left_bar']['plus']['fieldset_periode']['debut'] = array(
		'#type'        => 'textfield',
		'#title' 	   => t('Date debut'),
		'#prefix'	   =>'<table><tr><td>',
		'#description' => 'Format : "yyyy-mm-dd"',
		'#suffix'      =>'</td><td>',		
		);	

	$form['left_bar']['plus']['fieldset_periode']['fin'] = array(
		'#type' 	   => 'textfield',
		'#title'       => t('Date fin'),
		'#description' => 'Format : "yyyy-mm-dd"',
		'#suffix'      =>'</td></tr></table>',		
		);

	// Dates de modifications
	$form['left_bar']['plus']['fieldset_interval_date'] = array(
		'#type' => 'fieldset',
		'#title' => t('Dates de modification'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	$form['left_bar']['plus']['fieldset_interval_date']['after'] = array(
		'#type'        => 'textfield',
		'#title' 	   => t('Date debut'),
		'#prefix'	   =>'<table><tr><td>',
		'#description' => 'Format : "yyyy-mm-dd"',
		'#suffix'      =>'</td><td>',		
		);	

	$form['left_bar']['plus']['fieldset_interval_date']['before'] = array(
		'#type' => 'textfield',
		'#title' => t('Date fin'),
		'#description' => 'Format : "yyyy-mm-dd"',
		'#suffix'=>'</td></tr></table>',		
		);

	// Localisation

	$form['left_bar']['plus']['fieldset_where'] = array(
		'#type'        => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		);
	
	$form['left_bar']['plus']['fieldset_where']['spatialrel'] = array(
		'#type'          => 'radios',
		'#title'         => t('Où'),
		'#default_value' => '',
		'#options' => array(
			'' => t('Anywhere'), 
			'esriSpatialRelOverlaps' => t('Intersecting'),
			'esriSpatialRelWithin' => t('Fully within'),
			),
		);	
	$form['right_bar'] = array(
		'#type'        => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed'   => FALSE,
		'#attributes'  => array('class' => array('col-md-7')),
		);

	$form['right_bar']['recherche'] = array(
		'#type' => 'fieldset',
		'#title' => t('Recherche'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	// searchText.
	$form['right_bar']['recherche']['searchText'] = array(
		'#type'        => 'textfield',
		'#attributes'  => array('placeholder'=>array('search Text...')),
		);

	// Bouton de recherche.
	$form['right_bar']['recherche']['search'] = array(
		'#type'  => 'submit',
		'#value' => 'Chercher!',
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),
		//'#suffix'=>'</td></tr></table>',
		);
	
	$form['right_bar']['geoportal'] = array(
		'#type' => 'fieldset',
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	$form['right_bar']['geoportal']['results']= array(
		'#title' => t('Liste de métadonnées'),
		'#markup' => '<div id="geoContent" class="col-md-12">'.geoportal_recherche_callback($form,$form_state).'</div>',
		);

	return $form;
}

/*
 * 2. geoportal_recherche_form_ajax($form, &$form_state,$limit) : Est une fonction
 *    callback que j'ai crée et qui utilise ajax pour mêttre à jours la liste 
 *    des métadonnées à chaque fois qu'un paramètre dans le formulaire soit changé ou une
 *    recherche soit lancé. A son tours elle fait appelle à la fonction callback
 *    geoportal_recherche_callback($form, &$form_state).
 */
function geoportal_recherche_form_ajax($form, &$form_state) {
	$content = geoportal_recherche_callback($form,$form_state);
	
	$commands = array(
		ajax_command_html('#geoContent', $content),
		);
	$replace = array(
		'#type' => 'ajax',
		'#commands' => $commands,
		);
	return $replace;
}

/*
 * 3. geoportal_recherche_callback($form, &$form_state) : C'est une fonction callback
 *    dans laquelle se fait la préparation des paramètres des paramètres de l'API Esri 
 *    et l'execution de la requette 
 */
function geoportal_recherche_callback($form, &$form_state) {
	
	// Préparations des paramêtres de l'API Esri.

	$parametres='';
	
	// serachText
	if (!empty($form_state['values']['searchText'])) {
		$parametres .='searchText='.$form_state['values']['searchText'];
	}

	// La periode de données. 
	/*
	if (!empty($form_state['values']['debut']) and !empty($form_state['values']['fin'])) {
		$parametres .=' AND (timeperiod:['.$form_state["values"]["debut"].' TO '.$form_state["values"]["fin"].'])';
	}elseif (empty($form_state['values']['debut']) and !empty($form_state['values']['fin'])) {
		$parametres .=' AND (timeperiod:[* TO '.$form_state["values"]["fin"].'])';
	}elseif (!empty($form_state['values']['debut']) and empty($form_state['values']['fin'])) {
		$parametres .=' AND (timeperiod:['.$form_state["values"]["debut"].' TO *])';
	}
	*/
	
	
	// Catalogues

	/*
	// Avec les radios.
	if(!empty($form_state['values']['catalogues'])){
		$parametres .='&rid='.$form_state['values']['catalogues'];
		$parametres .='&rids='.$form_state['values']['catalogues'];
	}
	*/

	//*
	// Avec les checkboxes.
	$rid ='';
	if(!empty($form_state['values']['catalogues'])){
		foreach ($form_state['values']['catalogues'] as $args) {
			if ($args!='0') {
				$rid  = $args;
			}
		}
	}

	if(!empty($rid)){
		$parametres .='&rid='.$rid;
	}

	$rids ='';
	if(!empty($form_state['values']['catalogues'])){
		foreach ($form_state['values']['catalogues'] as $args) {
			if ($args!='0') {
				$rids.=$args.',';
			}
		}
	}

	if (!empty($rids)) {
		$parametres .='&rids='.substr($rids, 0, -1);
	}
	
	//*/

	// La donnée de départ 
	if (!empty($form_state['values']['start'])) {
		$parametres .='&start='.$form_state['values']['start'];
	}

	// Le nombre de données à afficher
	if (!empty($form_state['values']['max'])) {
		$parametres .='&max='.$form_state['values']['max'];
	}else{
		$parametres .='&max=100';
	}

	// spatialRel 
	if (!empty($form_state['values']['spatialrel'])) {
		$parametres .='&spatialRel='.$form_state['values']['spatialrel'];
	}

	// Content Type 
	if (!empty($form_state['values']['content_type'])) {
		$parametres .='&contentType='.$form_state['values']['content_type'];
	}

	// Data Category
	$dataCategory ='';
	if(!empty($form_state['values']['data_category'])){
		foreach ($form_state['values']['data_category'] as $args) {
			if ($args!='0') {
				$dataCategory.=$args.',';
			}
		}
	}

	if (!empty($dataCategory)) {
		$parametres .='&dataCategory='.substr($dataCategory, 0, -1);
	}

	// Date After.
	if (!empty($form_state['values']['after'])) {
		$parametres .='&after='.$form_state['values']['after'];
	}
	// Date Before.
	if (!empty($form_state['values']['before'])) {
		$parametres .='&before='.$form_state['values']['before'];
	}

	// Trier par
	if (!empty($form_state['values']['orderby'])) {
		$parametres .='&orderBy='.$form_state['values']['orderby'];
	}else{
		$parametres .='&orderBy=relevance';
	}

	// format de données.
	$parametres .='&f=json';
	// Création de la variable $url qui contient l'URL du portail de métadonnées
	// Plus les parametres de l'URL.
	$url = variable_get('geoportal_url','').'/rest/find/document?';

	// Faire appel à la fonction de drupal "drupal_http_request" pour exécuter
	// la requette http
	$request = drupal_http_request($url.$parametres);
	// Parser toutes les données renvoyées par la requêtte qui sont sous format 
	// json en format array.
	$request_array = drupal_json_decode($request->data);
	// Récupérer uniquements les métadonnées.
	$records = $request_array["records"];

	// Afficher les métadonnées dans un accordeon (voir accordeon boostrap).
	$content= '<div class="panel-group" id="accordion">';
	for ($i = 0; $i < sizeof($records); $i++) {
		$liens = '| ';
		$links = $records[$i]['links'];
		for ($j=0;$j<sizeof($links);$j++)
		{
			$liens .='<a href="'.$links[$j]['href'].'" target="blank">';
			$liens .=$links[$j]["type"].'</a> | ';
		}


		$content.= '<div class="panel panel-default">';
		$content.= '<div class="panel-heading">';
		$content.= '<h4 class="panel-title">';
		$content.= '<a data-toggle="collapse" data-parent="#accordion" href="#'.$i.'">'.$records[$i]["title"].'</a>';
		$content.= '</h4>';
		$content.= '</div>';
		$content.= '<div id="'.$i.'" class="panel-collapse collapse">';
		$content.= '<div class="panel-body">';
		$content.= '<p>'.$records[$i]['summary'].  '<a href="#" id="'.$records[$i]["id"].'" class="getDetail">détails</a></p>';
		$content.= '<footer class="text-right">'.$liens.'</footer>';
		$content.= '</div>';
		$content.= '</div>';
		$content.= '</div>';
	}  
	$content.= '</div>';

	return $content;
}

/*
 * 4. catalogues_rows() : Est une fonction qui retourne la liste des catalogues sous forme 
 * d’un tableau pour l’élément du formulaire (tableselect) qui affiche la liste des catalogues 
 * sous forme de liste de cases à cocher.
 *
 */
function catalogues_rows() {
	
	$query =db_select('geoportal_catalogs', 'c')
	->fields('c')
	->condition('status',1,'=')
	->orderby('cid','ASC');
	$results = $query->execute();

	$catalogs = array();
	$catalogs['local'] = t('Catalogues locaux');
	foreach ($results as $result) {
		$catalogs[$result->cid] = t('<span data-toggle="tooltip" data-placement="top" title="'.$result->description.'">'.$result->name.'</span>');
	}
	
	return $catalogs;
}

/*
 * 5. content_type_rows() : Est une fonction qui retourne la liste des content_type sous 
 * forme d’un tableau pour l’élément du formulaire (select) qui affiche les content types 
 * sous forme d’une liste déroulante.
 */
function content_type_rows() {
	return array(
		''                     =>'Any',
		'liveData'             =>'Live Map Services',
		'downloadableData'     =>'Downloadable Data',
		'offlineData'          =>'Offline Data',
		'staticMapImage'       =>'Static Map Images',
		'document'             =>'Documents',
		'application'          =>'Applications',
		'geographicService'    =>'Geographic Services',
		'clearinghouse'        =>'Clearinghouses',
		'mapFiles'             =>'Map Files',
		'geographicActivities' =>'Geographic Activities',
		'unknown'              =>'Resource',
		);
}

/*
 * 6. data_category_rows() : Est une fonction qui retourne la liste des data_category sous 
 * forme d’un tableau pour l’élément du formulaire (tableselect) qui affiche la liste des 
 * catalogues sous forme de liste de cases à cocher.
 */
function data_category_rows() {
	
	$query =db_select('geoportal_data_category', 'd')
	->fields('d')
	->condition('status',1,'=')
	->orderby('dcid','ASC');
	$results = $query->execute();

	$data_category = array();
	foreach ($results as $result) {
		$data_category[$result->dcid] = t($result->name);
	}
	
	return $data_category;
}