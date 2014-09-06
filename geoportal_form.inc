<?php
// 

/*
 * Dans ce fichier se trouve 6 fonctions :
 *
 * 1. geoportal_recherche_form($form,&$form_status)
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
function geoportal_recherche_form($form,&$form_status){

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
		'#options' => catalogues_rows(),
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),		
		);

	
	$form['left_bar']['recherche'] = array(
		'#type' => 'fieldset',
		'#title' => t('Recherche'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		);

	// searchText.
	$form['left_bar']['recherche']['searchText'] = array(
		'#type'        => 'textfield',
		'#description' => t('Tappez un mot clé ici'),
		'#attributes'  => array('placeholder' =>array('Tappez vos mos clés ici...')),
		);

	// Bouton de recherche.
	$form['left_bar']['recherche']['search'] = array(
		'#type'  => 'submit',
		'#value' => 'Chercher!',
		'#suffix'=>'',
		'#ajax' => array(
			'callback' => 'geoportal_recherche_form_ajax',
			'wrapper'  => 'geoContent',
			'method'   => 'html',
			),
		);

	// Lien sous form d'un bouton pour aller sur mapviewer.
	$form['left_bar']['recherche']['mapviewer'] = array(
		'#type' => 'link',
		'#title' => 'Map Viewer',
		'#href' => 'geoportal_mapviewer',
		'#attributes' => array('class' => array('btn btn-primary pull-right')),
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

	$form['right_bar']['geoportal']= array(
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

	//*
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
	$url ='http://vmportailmd-dev.mpl.ird.fr:8080/geoportal/rest/find/document?';
	//$url ='http://vmdevsi-geoportal.mpl.ird.fr:8080/geoportal/rest/find/document?';
	//$url ='http://gptogc.esri.com/geoportal/rest/find/document?';

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
	return array(
		'local'     => t('This Site'),
		'pigo'      => t('<span data-toggle="tooltip" data-placement="top" title="La plateforme d\'information géographique de Ouagadougou a pour objectif de collecter, d’harmoniser et de valoriser des données géographiques sur la ville de Ouagadougou issues de la recherche scientifique">PIGO : Portail de données géographiques sur la ville de Ougadougou</span>'),
		'neotec'    => t('<span data-toggle="tooltip" data-placement="top" title=" le projet de données NEOTEC-ouvert est de présenter un plan unifié de failles actives dans différents domaines tectoniques et climatiques de la Cordillère des Andes; diffuser de l\'information géoscientifique et proposer une communication scientifique en ligne." > NEOTEC : Neotectonic Open Data for South America</span>'),
		'picson'    => t('<span data-toggle="tooltip" data-placement="top" title="Portail  de l\'information géographique sur le Sud Ouest du Niger" > PICSON</span>'),
		'ammacatch' => t('<span data-toggle="tooltip" data-placement="top" title="Système d\'information pour la gestion des Ressources Naturelles et espaces du Bas Sénégal" > AMMA-CATCH : Mousson Afrique de l\'ouest</span>'),
		'sirena'    => t('<span data-toggle="tooltip" data-placement="top" title="Observatoire de la variabilité climatique et de son impact hydrologique en Afrique de l\'Ouest"> SIRENA : Biodiversité du fleuve Sénégal </span>'),
		);
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
	return array(	
		'boundaries'               => 'Administrative and Political Boundaries',
		'farming'                  => 'Agriculture and Farming',
		'climatologyMeteorologyAtmosphere' => 'Atmosphere and Climatic',
		'biota'                    => 'Biology and Ecology',
		'economy'                  => 'Business and Economic',
		'planningCadastre'         => 'Cadastral',
		'society'                  => 'Cultural, Society and Demography',
		'elevation'                => 'Elevation and Derived Products',
		'environment'              => 'Environment and Conservation',
		'structure'                => 'Facilities and Structures',
		'geoscientificInformation' => 'Geological and Geophysical',
		'health '                  => 'Human Health and Disease',
		'imageryBaseMapsEarthCover'=> 'Imagery and Base Maps',
		'inlandWaters'             => 'Inland Water Resources',
		'location'                 => 'Locations and Geodetic Networks',
		'intelligenceMilitary '    => 'Military',
		'oceans'                   => 'Oceans and Estuaries',
		'transportation'           => 'Transportation Networks',
		'utilitiesCommunication'   => 'Utilities and Communication',
		);
}