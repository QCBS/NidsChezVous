<?php

/**
 * Implements hook_block_info().
 */
function nids_block_info() {
	$blocks = array();
	$blocks['nids_list_nichoirs'] = array(
		'info' => t('A block to show nids_nichoirs datasets'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'explorer/nids_'
		);

	$blocks['nids_oiseaux_cour'] = array(
		'info' => t('A block to show nids_observations_dans_ta_cour datasets'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'explorer/oiseaux_cours'
		);

	$blocks['nids_oiseaux_ma_cour_list'] = array(
		'info' => t('A block to show nids_observations_dans_ta_cour datasets'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'explorer/observations_link'
		);
  //ajouter/danstacour/danstonichoir
	$blocks['nids_obsv_cour_nichoir'] = array(
		'info' => t('A block to show ajouter/danstacour/danstonichoir datasets'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'nids_obsv_cour_nichoir'
		);

	$blocks['nids_nichoirs_obs_list'] = array(
		'info' => t('A block to show the nichoir observations datasets'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'nids_oiseaux_cour_list'
		);
	$blocks['nids_list_own_nichoirs'] = array(
		'info' => t('A block to show your own nichoir'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'explorer/mes_nichoirs'
		);
		
	$blocks['home_page_data'] = array(
		'info' => t('A block to display some stats from the databases'),
		'cache' => DRUPAL_NO_CACHE,
		'region' => 'content',
		'status' => TRUE,
		'visibility' => BLOCK_VISIBILITY_LISTED,
		'pages' => 'home'
		);
	return $blocks;
}

function nids_block_obs_oiseaux(){
	$block = module_invoke('nids', 'block_view', 'nids_oiseaux_cour_liste');
	return $block['content'];
}

function nids_block_mes_obs_oiseaux(){
	$block = module_invoke('nids', 'block_view', 'nids_oiseaux_ma_cour_liste');
	return $block;
}

function nids_obsv3(){
	$block = module_invoke('nids', 'block_view', 'nids_nichoirs_obs_list_view');
	return $block['content'];
}
function nids_block_obsv_list(){ 
	$block = module_invoke('nids', 'block_view', 'nids_nichoirs_obs_list');
	return $block['content'];
}

function nids_blocklist(){
	$block = module_invoke('nids', 'block_view', 'nids_list_nichoirs');
	return $block['content'];
}

function nids_own_blocklist(){
	$block = module_invoke('nids', 'block_view', 'nids_list_own_nichoirs');
	return $block['content'];
}

function nids_list(){
	if(isset($_GET['filtre']) && $_GET['filtre']!='') { // Don't show map when there's a filter
		$output='';
	}else{
		$output=nids_map(970,550);
	}
	$output.=nids_blocklist();
	return $output;
}

function home_page_data(){
	$block = module_invoke('nids', 'block_view', 'home_page_data');
	return $block['content'];
}

/**
 * Implements hook_block_view().
 */
function nids_block_view($block_name = '') {
	$rows = array();
	$header = array();
	global $user;
	$user_role=db_select('users_roles','r')
	->fields('r',array('rid'))
	->condition('uid', $user->uid,'=')
	->execute()
	->fetchField();
	$isscientist=($user_role==3 || $user_role==6);

	if ($block_name == 'nids_list_nichoirs') {

		if ($isscientist){
			$header = array(
				array('data' => t('Numéro/Nom du Nichoir'), 'field' => 'dncv_no'),
				array('data' => t('Participant'), 'field' => 'nom_famille'),
				array('data' => t('Localisation'), 'field' => 'ecole'),
				array('data' => t('Date d\'installation'), 'field' => 'date_installation','sort'=>'desc'),
				array('data' => t('Habitat'), 'field' => 'habitat'),
				array('data' => t('Hauteur (mètres)'), 'field' => 'hauteur'),
				array('data' => t('Orientation'), 'field' => 'orientation'),
				array('data' => t('Occupé?')),
				);
		}else{
			$header = array(
				array('data' => t('Numéro/Nom du Nichoir'), 'field' => 'dncv_no'),
				array('data' => t('Localisation'), 'field' => 'ecole'),
				array('data' => t('Date d\'installation'), 'field' => 'date_installation','sort'=>'desc'),
				array('data' => t('Habitat'), 'field' => 'habitat'),
				array('data' => t('Hauteur (mètres)'), 'field' => 'hauteur'),
				array('data' => t('Orientation'), 'field' => 'orientation'),
				array('data' => t('Occupé?')),
				);
		}

		$query = db_select('nids_nichoirs', 'n')->extend('PagerDefault');
		$query->join('nids_users', 'u', 'n.uid = u.uid');
		$query->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
			'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 
			'habitat', 'hauteur', 'orientation', 'trou','type_nichoir'))
		->fields('u',array('prenom', 'nom_famille'));
		if(isset($_GET['filtre']) && $_GET['filtre']!='') {
		  $query->condition('dncv_no', db_like($_GET['filtre']), 'LIKE');
		}
		$query->extend('TableSort')->orderByHeader($header)
		->limit(100);

		$result = $query->execute();
		global $user;
		$user_role=db_select('users_roles','r')
		->fields('r',array('rid'))
		->condition('uid', $user->uid,'=')
		->execute()
		->fetchField();

		foreach ($result as $node1) {
			$isnode = node_load($node1->nid);
			$options = array('absolute' => TRUE);
			$url = url('node/'.$node1->nid, $options);
			$url2 = url('node/'.$node1->nid.'/view', $options);
			$urlu = url('user/'.$node1->uid.'/edit', $options);
			$edit='<a href='.$url.'/edit>Modifier</a>';
			$delete='<a href='.$url.'/delete>Supprimer</a>';
			
			if ($node1->parc!='')
				$parcecole=$node1->parc;
			else if ($node1->ecole!='')
				$parcecole=$node1->ecole;
			else
				$parcecole='Cours';

			$nomnumero = ($node1->type_nichoir=='Participant') ? $node1->nom_nichoir : $node1->type_nichoir.' #'.$node1->dncv_no;
			
			$nob = db_select('nids_nichoirs_obs', 'n')
			->fields('n',array('type_obs','oiseau_espece'))
			->condition('nid_id', $node1->nid,'=')
			->orderBy('obs_id', 'DESC')
			->execute()
			->fetchAssoc();
			
			if($nob['type_obs'] >= 9 || $nob['type_obs']==''){
				$ut='Non'; //Non Utilisé
				$sp='';
  			}
  			else
  				$ut='<img src="'.base_path().drupal_get_path('module','nids').'/images/green-check-mark.png" style="width:30px;height:30px">'.$nob['oiseau_espece'];
  			
  			if($isscientist){
  				$rows[] = array('<a href='.$url2.'>'.$nomnumero.'</a>', '<a href="'.$urlu.'">'. $node1->prenom. ' ' .$node1->nom_famille.'</a>',
  				$parcecole, $node1->date_installation, $node1->habitat, $node1->hauteur, $node1->orientation, $ut, $edit, $delete);
  			}
 		 	else
  				$rows[] = array($nomnumero, $parcecole, $node1->date_installation, $node1->habitat, $node1->hauteur, $node1->orientation,$ut);
		}
if(empty($header))
	$header = array(t('Numéro/Nom du Nichoir'),t('Participant'), t('Localisation'), 
		t('Date d\'installation'), t('Habitat'), t('Hauteur (mètres)'), 
		t('Orientation'),t('Occupé?'));


    //Return the content of the block
$content=drupal_render(drupal_get_form('nids_nichoirs_filter_form')).theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
$block = array(
	'subject' => t(''),
	'content' => $content,
	);
return $block;
}  

elseif ($block_name == 'nids_list_own_nichoirs') {
	$query = db_select('nids_nichoirs', 'n')->extend('PagerDefault');
	$query->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
		'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 
		'habitat', 'hauteur', 'orientation', 'trou','type_nichoir'))->condition('uid',$user->uid,'=')
		->limit(100);
	$result = $query->execute();
	$geog=array();
	foreach ($result as $node1) {
		$isnode = node_load($node1->nid);
		$options = array('absolute' => TRUE, 'query' => array('id' => $node1->nid, 'type' => "nichoir"));
		$options2 = array('absolute' => TRUE);
		$url = url('node/'.$node1->nid, $options2);
		$url2 = url('node/'.$node1->nid.'/view', $options);
		$edit='<a href='.$url.'/edit>Modifier</a>';
		$delete='<a href='.$url.'/delete>Supprimer</a>';
		
		if ($node1->parc!='')
			$parcecole=$node1->parc;
		else if ($node1->ecole!='')
			$parcecole=$node1->ecole;
		else
			$parcecole='Cours';

		$nomnumero = ($node1->type_nichoir=='Participant') ? $node1->nom_nichoir : $node1->type_nichoir.'#'.$node1->dncv_no;
		$nob = db_select('nids_nichoirs_obs', 'n')
		->fields('n',array('type_obs'))
		->condition('nid_id', $node1->nid,'=')
		->orderBy('obs_id', 'DESC')
		->execute()
		->fetchField();
		
		$ut = ($nob[0]>9 || $nob[0]=='')?'Non':'Oui';
		$header = array(t('Numéro/Nom du Nichoir'), t('Localisation'), 
			t('Date d\'installation'), t('Habitat'), t('Hauteur (mètres)'), t('Orientation'),t('Occupé?')); 
			     
		$rows[] = array('<a href='.$url2.'>'.$nomnumero.'</a>', $parcecole, $node1->date_installation, $node1->habitat, $node1->hauteur, $node1->orientation, $ut, $edit, $delete);
		$iw="<div><h2><b>".(($node1->dncv_no!='')?'DNCV #'.$node1->dncv_no:$node1->nom_nichoir)."</b></h2><div>".(($node1->parc!='')?$node1->parc:'').(($node1->ecole!='')?$node1->ecole:'')."</div>Date d&#39;installation: ".$node1->date_installation."</div>";
		$geo=json_decode($node1->geography);
		$geo->features[0]->properties=array(
			'nid'=>$node1->nid,
			'infowin'=>$iw,
			'utilise'=>$ut,
			);    
		$geog[]=$geo->features[0];
    //$output.="";
	}

	drupal_add_js('http://maps.google.com/maps/api/js?sensor=false');
	drupal_add_js(base_path().drupal_get_path('module', 'nids') . '/javascript/nids.map.js');
	drupal_add_js(array('nids_mode' => 'view'), 'setting');

    //Return the content of the block
	$arr=array(
		'type'=>'FeatureCollection',
		'features' => $geog,
		);
	$content="<input type='hidden' name='geography' value='".json_encode($arr,JSON_UNESCAPED_SLASHES)."'>";
	$content.="<div id='map' style='width: 100%;height: 500px;max-width: 95%;max-height: 85%;'></div><br><br>";
	$content.=theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	$block = array(
		'subject' => t(''),
		'content' => $content,
		);
	return $block;

} 

elseif ($block_name == 'nids_oiseaux_cour_liste') {
	if ($isscientist){
		$header = array(
			array('data' => t('Participant')),
			array('data' => t('Date d\'observation'), 'field' => 'date_obs', 'sort' => 'desc'),
			array('data' => t('Durée d\'observation (min)'), 'field' => 'duree_obs'),
			array('data' => t('Espèce'), 'field' => 'oiseau_espece'),
			array('data' => t('Nombre d\'individus'), 'field' => 'nombre_individus'),
			);
	}else{
		$header = array(
			array('data' => t('Date d\'observation'), 'field' => 'date_obs', 'sort' => 'desc'),
			array('data' => t('Durée d\'observation (min)'), 'field' => 'duree_obs'),
			array('data' => t('Espèce'), 'field' => 'oiseau_espece'),
			array('data' => t('Nombre d\'individus'), 'field' => 'nombre_individus'),
			);
	}
	$query2=db_select('nids_oiseaux_cour','t')->extend('PagerDefault');
	$query2->join('nids_users', 'u', 't.uid = u.uid');
	$query2->fields('t',array('obs_id', 'uid', 'ecole', 'date_obs',
		'rien_vu', 'duree_obs', 'oiseau_espece', 'nombre_individus'))
	->fields('u',array('prenom', 'nom_famille'))->extend('TableSort')->orderByHeader($header)
	->limit(100);
	$result = $query2->execute();

	foreach ($result as $node2) {
		$isnode = node_load($node2->obs_id);
		$oiseau = ($node2->rien_vu == 1)? 'Rien observé' : $node2->oiseau_espece;

		if ($isscientist){
			$options = array('absolute' => TRUE, 'query' => array('id' => $node2->obs_id, 'type' => "observation"));
			//cour_obs or ecole_obs ?
			if(empty($node2->ecole)){
				$url = url('cour_obs', $options);
				$ecole = 'Cours';
			}
			else{
				$url = url('ecole_obs', $options);
				$ecole = $node2->ecole;
			}
		
			$urlDel = url('supprimer', $options);
			$edit='<a href='.$url.'>Edit</a>';
			$delete='<a href='.$urlDel.'>Supprimer</a>';
			
			$header = array(t('Participant'), t('Emplacement'), t('Date d\'observation'), t('Durée d\'observation (min)'), t('Espèce'),t('Nombre d\'individus'));      
			$rows[] = array($node2->prenom. ' ' .$node2->nom_famille, $ecole, $node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus, $edit, $delete);
		}
		else {
			$header = array(t('Date d\'observation'), t('Durée d\'observation (min)'), t('Espèce'),t('Nombre d\'individus'));      
			$rows[] = array($node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus);
		}
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	$block = array(
		'subject' => t('Liste d\'observations dans toutes les cours'),
		'content' => $content,
		);
	return $block;
}

elseif ($block_name == 'nids_oiseaux_ma_cour_liste') {
	
	$header = array(t('Date d\'observation'), t('Durée d\'observation (min)'), t('Espèce'),t('Nombre d\'individus'));
	$query2=db_select('nids_oiseaux_cour','t')->extend('PagerDefault'); 
	$query2->fields('t',array('obs_id', 'uid', 'date_obs', 
		'rien_vu', 'duree_obs', 'oiseau_espece', 'nombre_individus'))->extend('TableSort')->orderByHeader($header)
		->condition('uid',$user->uid,'=')
		->condition('ecole','','=')
		->orderBy('obs_id', 'DESC')
		->limit(100);
	$result = $query2->execute();
	foreach ($result as $node2) {
		$options = array('absolute' => TRUE, 'query' => array('id' => $node2->obs_id, 'type' => "observation"));
		//$url = url($node2->oiseau_espece, $options); //For future purposes
		
		$url = url('cour_obs', $options);
		$urlDel = url('supprimer', $options);
		$edit='<a href='.$url.'>Edit</a>';
		$delete='<a href='.$urlDel.'>Supprimer</a>';
		
		($node2->rien_vu == 1)? $oiseau = 'Rien observé' : $oiseau = $node2->oiseau_espece;
		$rows[] = array($node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus, $edit, $delete);
	}

	$content=theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	$block = array(
		'subject' => '',
		'content' => $content,
		);
	return $block;
}

elseif ($block_name == 'nids_nichoirs_obs_list') {
	if ($isscientist){
		$header = array(
			array('data'=>t('Participant'),'field' => 'nom_famille'), 
			array('data'=>t('Date d\'observation'),'field' => 'date_obs', 'sort' => 'desc'),
			array('data'=>t('Oiseau èspece'),'field' => 'oiseau_espece'), 
			array('data'=>t('Type d\'observation'),'field' => 'type_obs'),
			);
	}
	else{
		$header = array(
			array('data'=>t('Date d\'observation'),'field' => 'date_obs', 'sort' => 'desc'),
			array('data'=>t('Oiseau èspece'),'field' => 'oiseau_espece'), 
			array('data'=>t('Type d\'observation'),'field' => 'type_obs'),
			);
		}
	$query3=db_select('nids_nichoirs_obs','t')->extend('PagerDefault');
	$query3->join('nids_users', 'u', 't.uid = u.uid');
	$query3->fields('t',array('obs_id', 'uid', 'nid_id', 'date_obs', 
		'rien_vu', 'oiseau_espece', 'oiseau_espece_autre', 'type_obs', 'type_obs_autre'))
	->fields('u',array('prenom', 'nom_famille'))->extend('TableSort')->orderByHeader($header)
	->limit(100);
	$result = $query3->execute();

	foreach ($result as $node3) {
		$isnode = node_load($node3->obs_id);
		$options = array('absolute' => TRUE);
		$url = url($node3->oiseau_espece, $options);
		if(empty($node3->oiseau_espece))
			$myObs = $node3->oiseau_espece_autre;
		if(empty($node3->oiseau_espece_autre))
			$myObs = $node3->oiseau_espece;

		$typeObsv = (_nichoir_type_observation($node3->type_obs) == 'Autre' ? $node3->type_obs_autre : _nichoir_type_observation($node3->type_obs));

		if($node3->rien_vu == 1) {
			$myObs = 'Je n\'ai rien vu';
			$typeObsv = 'Aucune';
		}
		if ($isscientist){
			$options3 = array('query' => array('id' => $node3->obs_id, 'type' => "observation_nids"));
			$url3 = url('nichoir', $options3);
			$edit='<a href='.$url3.'>Edit</a>';
			
			$urlDel = url('supprimer', $options3);
			$delete='<a href='.$urlDel.'>Supprimer</a>';
			
			$rows[] = array($node3->prenom. ' ' .$node3->nom_famille, $node3->date_obs, $myObs, $typeObsv, $edit, $delete);
		}
		else {
			$rows[] = array($node3 ->date_obs, $myObs, $typeObsv);
		}
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');

	$block = array(
		'subject' => t('List of nids observations datasets'),
		'content' => $content,
		);
	return $block;
}
// Same as previous block view but for one item so it has an extra condition
elseif ($block_name == 'nids_nichoirs_obs_list_view') {
	$myNode = menu_get_object();
	$myNode2 = $myNode->nid;
	$query5=db_select('nids_nichoirs_obs','t')->extend('PagerDefault');
	$query5->join('nids_users', 'u', 't.uid = u.uid');
	$query5->fields('t',array('obs_id', 'uid', 'nid_id', 'date_obs', 
		'rien_vu', 'oiseau_espece', 'oiseau_espece_autre', 'type_obs', 'type_obs_autre'))
	->fields('u',array('prenom', 'nom_famille'))
	->condition('nid_id',$myNode2,'=')
	->limit(100);
	$result = $query5->execute();

	foreach ($result as $node3) {
		$isnode = node_load($node3->obs_id);
		$options = array('absolute' => TRUE);

		if(isset($node3->oiseau_espece))
			$myObs = $node3->oiseau_espece_autre;
		if(isset($node3->oiseau_espece_autre))
			$myObs = $node3->oiseau_espece;
		$typeObsv = (_nichoir_type_observation($node3->type_obs) == 'Autre' ? $node3->type_obs_autre : _nichoir_type_observation($node3->type_obs));

		if($node3->rien_vu == 1) {
			$myObs = 'Je n\'ai rien vu';
			$typeObsv = 'Aucune';
		}
	
		if ($isscientist){
			$options2 = array('query' => array('id' => $node3->obs_id, 'type' => "observation_nids"));
			$url = url('nichoir', $options2);
			$edit='<a href='.$url.'>Edit</a>';
			$url2 = url('supprimer', $options2);
			$delete='<a href='.$url2.'>Supprimer</a>';
			$rows[] = array($node3->prenom. ' ' .$node3->nom_famille, $node3->date_obs, $myObs, $typeObsv, $edit, $delete);
			$header = array(t('Participant'), t('Date d\'Observation'), t('Oiseau Èspece'), t('Type d\'Observation'));
		}
		else {
			$rows[] = array($node3->date_obs,$myObs, $typeObsv);
			$header = array(t('Date d\'Observation'), t('Oiseau Èspece'), t('Type d\'Observation'));
		}
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows)).theme('pager');
	$block = array(
		'subject' => t('List of nids observations datasets'),
		'content' => $content,
		);
	return $block;
} 
// Home page block view

elseif ($block_name == 'home_page_data') {
	$myInfo = array('numParticipants' => getCount('nids_users', false), 'numNests' => getCount('nids_nichoirs', false), 
					'numEspeces' => getCount('nids_oiseaux_cour', true), 'numObservations' => getCount('nids_oiseaux_cour',false),
					'numOccuper' => getCount('nids_nichoirs_obs', true));

//	$myInfo['numOccuper']=21; //Remove for 2015!!!!!
	$content=
	'<div style="margin: -30px 5px 10px 10px;">
		<text style="font-size: 25px;font-weight:bold;">' .$myInfo['numParticipants']. '</text> participants  &nbsp&nbsp
		<text style="font-size: 25px;font-weight:bold;">' .$myInfo['numNests']. '</text> nichoirs installés   &nbsp&nbsp
		<text style="font-size: 25px;font-weight:bold;">' .$myInfo['numOccuper']. '</text> nichoirs occupés en 2018   &nbsp&nbsp
		<text style="font-size: 25px;font-weight:bold;">' .$myInfo['numObservations']. '</text> observations d\'oiseaux de &nbsp
		<text style="font-size: 25px;font-weight:bold;">' .$myInfo['numEspeces']. '</text> espèces différentes dans les cours
	</div>';
    //Return the content of the block
	$block = array(
		'subject' => t('List of nids observations datasets'),
		'content' => $content, //drupal_render($content),
		);
	return $block;
}
}
function getCount($myTable, $all){
	if($myTable === 'nids_oiseaux_cour' && $all === true){
		$query1=db_select($myTable,'u')
		->fields('u', array('oiseau_espece'))
		->distinct()
		->execute();
		$numRows = $query1->rowCount();
	}
	elseif($myTable === 'nids_nichoirs_obs' && $all === true){
		
		$query1=db_query("SELECT count(DISTINCT b.nid_id) AS cnt FROM ( SELECT nids_nichoirs_obs.obs_id AS mid, nids_nichoirs_obs.nid_id FROM nids_nichoirs_obs GROUP BY nids_nichoirs_obs.nid_id, nids_nichoirs_obs.obs_id HAVING  date_obs=max(date_obs)) a, nids_nichoirs_obs b WHERE a.mid = b.obs_id AND date_obs>'2018-01-01' AND NULLIF(b.type_obs::text, ''::text)::integer <= 8")->fetchField();
		$numRows=$query1;
	}
	else{
		$query1=db_select($myTable,'u')
		->fields('u')
		->execute();
		$numRows = $query1->rowCount();
	}
	return $numRows;
}

?>