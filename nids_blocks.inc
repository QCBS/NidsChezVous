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

	$blocks['nids_oiseaux_ma_cour_liste'] = array(
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
	return $block;
}

function nids_list(){
	$output=nids_map(900,500).nids_blocklist();
	return $output;
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

		$query = db_select('nids_nichoirs', 'n');
		$query->join('nids_users', 'u', 'n.uid = u.uid');
		$query->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
			'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 
			'habitat', 'hauteur', 'orientation', 'trou'))
		->fields('u',array('prenom', 'nom_famille'))->extend('TableSort')->orderByHeader($header);

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
			if(node_access('update',$node1->nid)){
				$edit='<a href='.$url.'/edit>Edit</a>';
				$urlu = url('user/'.$node1->uid.'/edit', $options);
			}else{
				$edit='';
			}

			if ($node1->parc!='')
				$parcecole=$node1->parc;
			else if ($node1->ecole!='')
				$parcecole=$node1->ecole;
			else
				$parcecole='Cours';

			$nomnumero = ($node1->dncv==0) ? $node1->nom_nichoir : 'DNCV #'.$node1->dncv_no;
			$nob = db_select('nids_nichoirs_obs', 'n')->fields('n',array('type_obs','oiseau_espece'))->condition('nid_id', $node1->nid,'=')->orderBy('obs_id', 'DESC')->execute()->fetchAssoc();
			if($nob['type_obs'] >= 9 || $nob['type_obs']==''){
      $ut='Non'; //Non Utilisé
      $sp='';
  }else{
  	$ut='<img src="'.base_path().drupal_get_path('module','nids').'/images/green-check-mark.png" style="width:30px;height:30px">'.$nob['oiseau_espece'];
  }
  if ($isscientist){

  	$rows[] = array('<a href='.$url2.'>'.$nomnumero.'</a>', '<a href="'.$urlu.'">'.
  		$node1->prenom. ' ' .$node1->nom_famille.'</a>', $parcecole, $node1->date_installation, $node1->habitat, $node1->hauteur, 
  		$node1->orientation, $ut, $edit);
  }
  else {
  	$rows[] = array($nomnumero, $parcecole, 
  		$node1->date_installation, $node1->habitat, $node1->hauteur, $node1->orientation,$ut);
  }
}
if(empty($header))
	$header = array(t('Numéro/Nom du Nichoir'),t('Participant'), t('Localisation'), 
		t('Date d\'installation'), t('Habitat'), t('Hauteur (mètres)'), 
		t('Orientation'),t('Occupé?'));

    //Return the content of the block
$content=theme('table', array('header' => $header, 'rows' => $rows));
$block = array(
	'subject' => t(''),
	'content' => $content,
	);
return $block;
}  elseif ($block_name == 'nids_list_own_nichoirs') {
	$query = db_select('nids_nichoirs', 'n');
	$query->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
		'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 
		'habitat', 'hauteur', 'orientation', 'trou'))->condition('uid',$user->uid,'=');

	$result = $query->execute();
	$geog=array();
	foreach ($result as $node1) {
		$isnode = node_load($node1->nid);
		$options = array('absolute' => TRUE);
		$url = url('node/'.$node1->nid, $options);
		$url2 = url('node/'.$node1->nid.'/view', $options);
		$edit='<a href='.$url.'/edit>Modifier</a>';

		if ($node1->parc!='')
			$parcecole=$node1->parc;
		else if ($node1->ecole!='')
			$parcecole=$node1->ecole;
		else
			$parcecole='Cours';

		$nomnumero = ($node1->dncv==0) ? $node1->nom_nichoir : 'DNCV #'.$node1->dncv_no;
		$nob = db_select('nids_nichoirs_obs', 'n')->fields('n',array('type_obs'))->condition('nid_id', $node1->nid,'=')->orderBy('obs_id', 'DESC')->execute()->fetchField();
		$ut = ($nob[0]>9 || $nob[0]=='')?'Non':'Oui';
		$header = array(t('Numéro/Nom du Nichoir'), t('Localisation'), 
			t('Date d\'installation'), t('Habitat'), t('Hauteur (mètres)'), t('Orientation'),t('Occupé?'));      
		$rows[] = array('<a href='.$url2.'>'.$nomnumero.'</a>', $parcecole, $node1->date_installation, $node1->habitat, $node1->hauteur, 
			$node1->orientation, $ut, $edit);
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
	$content.=theme('table', array('header' => $header, 'rows' => $rows));
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

	$query2=db_select('nids_oiseaux_cour','t');
	$query2->join('nids_users', 'u', 't.uid = u.uid');
	$query2->fields('t',array('obs_id', 'uid', 'date_obs', 'rien_vu', 'duree_obs', 'oiseau_espece', 'nombre_individus'))
	->fields('u',array('prenom', 'nom_famille'))->extend('TableSort')->orderByHeader($header); 
	$result = $query2->execute();

	foreach ($result as $node2) {
		$isnode = node_load($node2->obs_id);
		$options = array('absolute' => TRUE);
		$url = url($node2->oiseau_espece, $options);
		($node2->rien_vu == 1)? $oiseau = 'Rien observé' : $oiseau = $node2->oiseau_espece;

		if ($isscientist){

			$rows[] = array($node2->prenom. ' ' .$node2->nom_famille, $node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus);
		}
		else {
			//$header = array(t('Date d\'observation'), t('Durée d\'observation (min)'), t('Espèce'),t('Nombre d\'individus'));      
			$rows[] = array($node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus);
		}
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows));
	$block = array(
		'subject' => t('Liste d\'observations dans les cours'),
		'content' => $content,
		);
	return $block;
}
elseif ($block_name == 'nids_oiseaux_ma_cour_liste') {
	$query2=db_select('nids_oiseaux_cour','t');
	$header = array(t('Date d\'observation'), t('Durée d\'observation (min)'), t('Espèce'),t('Nombre d\'individus')); 
	$query2->fields('t',array('obs_id', 'uid', 'date_obs', 
		'rien_vu', 'duree_obs', 'oiseau_espece', 'nombre_individus'))->extend('TableSort')->orderByHeader($header)->condition('uid',$user->uid,'=')->condition('ecole','','=')->orderBy('obs_id', 'DESC');

	$result = $query2->execute();
	foreach ($result as $node2) {
		$isnode = node_load($node2->obs_id);
		$options = array('absolute' => TRUE);
		$url = url($node2->oiseau_espece, $options);
		($node2->rien_vu == 1)? $oiseau = 'Rien observé' : $oiseau = $node2->oiseau_espece;
		$rows[] = array($node2->date_obs, $node2->duree_obs, $oiseau, $node2->nombre_individus);
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows));
	$block = array(
		'subject' => t(''),
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
}else{
$header = array(
		array('data'=>t('Date d\'observation'),'field' => 'date_obs', 'sort' => 'desc'),
		array('data'=>t('Oiseau èspece'),'field' => 'oiseau_espece'), 
		array('data'=>t('Type d\'observation'),'field' => 'type_obs'),
		);}

	$query3=db_select('nids_nichoirs_obs','t');
	$query3->join('nids_users', 'u', 't.uid = u.uid');
	$query3->fields('t',array('obs_id', 'uid', 'nid_id', 'date_obs', 
		'rien_vu', 'oiseau_espece', 'oiseau_espece_autre', 'type_obs', 'type_obs_autre'))
	->fields('u',array('prenom', 'nom_famille'))->extend('TableSort')->orderByHeader($header);

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
			$rows[] = array($node3->prenom. ' ' .$node3->nom_famille,
				$node3->date_obs, $myObs, $typeObsv);
		}
		else {
			$rows[] = array($node3 ->date_obs, $myObs, $typeObsv);
		}
	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows));

	$block = array(
		'subject' => t('List of nids observations datasets'),
		'content' => $content,
		);
	return $block;
}
elseif ($block_name == 'nids_type_obs') {
	$query4=db_select('nids_nichoir_type_obs','t');
	$query4->fields('t',array('type_obs_id', 'type_obs_key', 'description'));
	$result = $query4->execute();
	$header = array(t('Type d\'Observation ID'), t('Type d\'Observation Key'), t('Description'));

	$isnode = node_load($node4->obs_id);
	$options = array('absolute' => TRUE);

	$rows[] = array($node4->type_obs_id, $node4->type_obs_key, $node4->description);

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows));
	$block = array(
		'subject' => t('List of nids observation in dans ta Cour datasets'),
		'content' => $content,
		);
	return $block;
}
  	 // This is for the "View" when in nids_node_view(), it has an extra condition
elseif ($block_name == 'nids_nichoirs_obs_list_view') {
	$myNode = menu_get_object();
	$myNode2 = $myNode->nid;
	$query5=db_select('nids_nichoirs_obs','t');
	$query5->join('nids_users', 'u', 't.uid = u.uid');
	$query5->fields('t',array('obs_id', 'uid', 'nid_id', 'date_obs', 
		'rien_vu', 'oiseau_espece', 'oiseau_espece_autre', 'type_obs', 'type_obs_autre'))
	->fields('u',array('prenom', 'nom_famille'))
	->condition('nid_id',$myNode2,'=');
	$result = $query5->execute();


	foreach ($result as $node3) {

		$isnode = node_load($node3->obs_id);
		$options = array('absolute' => TRUE);
		$url = url($node3->oiseau_espece, $options);
		
		$url2 = url('node/'.$node3->obs_id, $options);
		if(node_access('update',$node3->obs_id)){
			$edit='<a href='.$url2.'/edit/obs_id>Edit</a>';
			$urlu = url('user/'.$node3->obs_id.'/edit', $options);
		}
		else
			$edit='';
		
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
			$rows[] = array($node3->prenom. ' ' .$node3->nom_famille, $node3->date_obs, $myObs, $typeObsv, $edit);
			$header = array(t('Participant'), t('Date d\'Observation'), t('Oiseau Èspece'), t('Type d\'Observation'));
		}
		else {
			$rows[] = array($node3->date_obs,$myObs, $typeObsv);
			$header = array(t('Date d\'Observation'), t('Oiseau Èspece'), t('Type d\'Observation'));
		}

	}

    //Return the content of the block
	$content=theme('table', array('header' => $header, 'rows' => $rows));
	$block = array(
		'subject' => t('List of nids observations datasets'),
		'content' => $content,
		);
	return $block;
} 

}



?>