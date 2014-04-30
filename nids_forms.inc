<?php
function nids_form_alter(&$form, &$form_state, $form_id) {

  if($form_id == 'nichoir_node_form') {
    drupal_add_js(array('nids_mode' => 'edit'), 'setting');

    $form['dncv'] = array(
      '#title' => t("Est-ce un nichoir construit par Des nids chez vous?"),
      '#type' => 'select',
      '#required' => TRUE,
      '#default_value' => isset($form['#node']->dncv) ? $form['#node']->dncv : "",
      '#options' => array(
        1 => 'Oui',
        0 => 'Non',
        ),
      );

    $form['numero'] = array(
      '#title' => t("Quel est le numéro du nichoir?"),
      '#type' => 'textfield',
      '#required' => FALSE,
      '#size' => 15,
      '#default_value' => isset($form['#node']->dncv_no) ? $form['#node']->dncv_no : "",
      '#states' => array(
        'visible' => array(
          ':input[name="dncv"]' => array('value' => "1")
          ),
        ),
      );

    $form['nom_nichoir'] = array(
      '#title' => t("Quel nom voulez-vous donner à ce nichoir (par ex. cabanon, bouleau)?"),
      '#type' => 'textfield',
      '#size' => 35,
      '#required' => FALSE,
      '#default_value' => isset($form['#node']->nom_nichoir) ? $form['#node']->nom_nichoir : "",
      '#states' => array(
        'visible' => array(
          ':input[name="dncv"]' => array('value' => "0")
          ),
        ),
      );

    global $user;
    $user_role=db_select('users_roles','r')
    ->fields('r',array('rid'))
    ->condition('uid', $user->uid,'=')
    ->execute()
    ->fetchField();

    $isscientist=($user_role==3 || $user_role==6);
    $form['scientist'] = array(
      '#type' => 'hidden',
    //'#default_value' => $user_role,
      '#default_value' => ($isscientist?1:0),
      );


    $form['dans_un_parc_ecole'] = array(
      '#title' => t("Est-ce un dans une école ou dans un parc?"),
      '#type' => 'select',
      '#options' => array( 
        'Non' => 'Non',
        'Parc' => 'Parc',
        'École' => 'École',
        ),
      '#required' => FALSE,
      '#default_value' => isset($form['#node']->dans_un_parc_ecole) ? $form['#node']->dans_un_parc_ecole : "",
      '#states' => array(
        'visible' => array(
          ':input[name="scientist"]' => array('value' => "1"),
          )
        ),
      );
    $form['parc'] = array(
      '#title' => t("Pour quel parc?"),
      '#type' => 'select',
      '#options' => array(
        null => 'Choisir...',
        //'Lepage' => 'Lepage',
        'Parc Beauséjour' => 'Parc Beauséjour',
        'Parc La gare' => 'Parc La gare',
        'Parc Mont-Saint-Louis' => 'Parc Mont-Saint Louis',
        'Parc Mairie Saint-Anaclet' => 'Parc Mairie Saint-Anaclet',
        'Bibliothèque Lisette-Morin' =>'Bibliothèque Lisette-Morin',
        ),
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(
          ':input[name="scientist"]' => array('value' => "1"),
          ':input[name="dans_un_parc_ecole"]' => array('value' => 'Parc'),
          )
        ),
      '#default_value' => isset($form['#node']->parc) ? $form['#node']->parc : "",
      );

    $form['ecole'] = array(
      '#title' => t("Nom de l'école"),
      '#type' => 'select',
      '#options' => array(
        null => 'Choisir...',
        'École Rose des Vents' => 'École Rose des Vents',
        'École des Sources' => 'École des Sources',
        'École du Rocher-Auteuil' => 'École du Rocher-Auteuil',
        'École Mont Saint-Louis' => 'École Mont Saint-Louis',
        'École Saint-Rosaire' => 'École Saint-Rosaire',
        ),
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(
          ':input[name="scientist"]' => array('value' => "1"),
          ':input[name="dans_un_parc_ecole"]' => array('value' => 'École'),
          )
        ),
        '#default_value' => isset($form['#node']->ecole) ? $form['#node']->ecole : "",
      );


    $form['geo'] = array(
      '#title' => t(''),
      '#type' => 'fieldset',
      );

if (isset($form['#node']->uid)){
  $uid=$form['#node']->uid;
}else{
  $uid=$user->uid;
}

    $form['user'] = array(
      '#type' => 'hidden',
      '#size' => 100,
      '#required' => FALSE,
      //'#suffix' => '<div id="noloc" style="display:none;">'.t('Ce nom ne peut être reconnu!').'</div><button type="button" id="addbynamebut">'.t('Ajouter un marqueur à cet endroit sur la carte (OPTION 1)').'</button>',
      '#default_value' => $uid,
      );

    $adresse=db_select('nids_users','n')
    ->fields('n')
    ->condition('uid',$uid,'=')
    ->execute();

    if ($adresse->rowCount()>0){
      $adresse=$adresse->fetchAssoc();
      $add=$adresse['adresse'].', '.$adresse['code_postal'].', '.$adresse['ville'];
    }else{
      $add='';
    }
    $form['geo']['location_name'] = array(
      '#type' => 'hidden',
      '#size' => 100,
      '#required' => FALSE,
      '#prefix' => '<div id="adresse" style="display:none;">'.$add.'</div><div class="nidsbox"></div><h2>'.t('Lieu du nichoir').'</h2>',
      //'#suffix' => '<div id="noloc" style="display:none;">'.t('Ce nom ne peut être reconnu!').'</div><button type="button" id="addbynamebut">'.t('Ajouter un marqueur à cet endroit sur la carte (OPTION 1)').'</button>',
      '#default_value' => ""
      );

    $form['geo']['geography'] = array(
      '#title' => t('Lieu du nichoir'),
      '#type' => 'hidden',
      '#size' => 200,
      '#required' => FALSE,
      '#default_value' => isset($form['#node']->geography) ? $form['#node']->geography : "",
      /*'#suffix' => '<h3>'.t('<strong>ou</strong>, si vous les connaissez, ajouter les coordonnées géographiques du nichoir en format latitude, longitude dans cette boîte (e.g. 48.3732, -68.7041).</h3>').'
      <br><input type="text" id="inputcoords" style="display:inline;width:200px;">
      <button type="button" id="inputcoordsbut" class="nids-button" style="display:inline;" >'.t('Ajouter un marqueur à ces coordonnées sur la carte').'</button>
      <div id="coorderror" style="display:none;">'.t('Coordonnées non reconnues!').'</div>
    </p>',
    */
    '#prefix' => '<h3>'.t('Situe le nichoir en déplacant le marqueur (icône de nichoir orange) sur la carte').'</h3><div id="map" style="width:700px;height:500px;"></div></div>',
    
    /*<p><button type="button" id="pointbut">'.t('Ajoute un nichoir en cliquant sur la carte').'</button>
    <button type="button" id="nids-clear">'.t('Effacer').'</button>
  </p>*/
  );

$form['date_installation'] = array(
  '#type' => 'date_popup',
  '#date_format' => 'Y-m-d',
  '#size' => 30,
  '#datepicker_options' => array('maxDate' => date('Y-m-d H:i')),
  '#title' => "Date de l'installation du nichoir",
  '#required' => FALSE,
  '#default_value' => isset($form['#node']->date_installation) ? $form['#node']->date_installation : ""
  );

$form['habitat'] = array(
  '#title' => t("Le nichoir est fixé à..."),
  '#type' => 'select',
  '#required' => FALSE,
  '#default_value' => isset($form['#node']->habitat) ? $form['#node']->habitat : "",
  '#options' => array(
    'choisir' => 'Choisir...',
    'batiment' => 'bâtiment',
    'arbre' => 'arbre',
    'cloture' => 'clôture',
    'poteau' => 'poteau',
    ),
  );

$form['hauteur'] = array(
  '#title' => t("À quelle hauteur est situé le nichoir (en mètres)?"),
  '#type' => 'textfield',
  '#required' => FALSE,
  '#default_value' => isset($form['#node']->hauteur) ? $form['#node']->hauteur : "",
  '#size'=> 30,
  );

$form['trou'] = array(
  '#title' => t("Quelle est la taille du trou (en centimètres) dans le nichoir?"),
  '#type' => 'textfield',
  '#required' => FALSE,
  '#default_value' => isset($form['#node']->trou) ? $form['#node']->trou : "",
  '#states' => array(
     'visible' => array(
       ':input[name="dncv"]' => array('value' => "0")
      ),
  ),
  '#size'=> 30,
  );

$form['orientation'] = array(
  '#title' => t("Orientation du nichoir"),
  '#type' => 'select',
  '#options' => array(
    null => 'Choisir...',
    'Nord' => 'Nord',
    'Sud' => 'Sud',
    'Est' => 'Est',
    'Ouest' => 'Ouest',
    'Nord_est' => 'Nord-Est',
    'Nord_ouest' => 'Nord-Ouest',
    'Sud_est' => 'Sud-Est',
    'Sud_ouest' => 'Sud-Ouest',
    'Inconnue' => 'Inconnue',
    ),
  '#required' => FALSE,
  '#default_value' => isset($form['#node']->orientation) ? $form['#node']->orientation : "",
  );

$module_path = base_path().drupal_get_path('module', 'nids');

$js_files = array(
  'http://maps.google.com/maps/api/js?sensor=false',
  $module_path . '/javascript/nids.map.js',
  $module_path . '/javascript/selectboxit.js',
  $module_path . '/javascript/nids.jqueryui.js',      
  );
$form['#attached']['js'] = $js_files;
$form['#validate'][] = 'nichoir_form_validate';
$form['#submit'][] = 'nichoir_form_submit';
$form['additional_settings']['#access'] = FALSE;
$form['options']['status']['#default_value'] = TRUE;
$form['options']['status']['#input'] = TRUE;
$form['options']['status']['#return_value'] = TRUE;
$form['options']['status']['#value'] = TRUE;
$form['options']['status']['#checked'] = TRUE;
drupal_set_title(t("Ajouter un nichoir"));
return $form;
}
else if($form_id == 'user_register_form' | $form_id == 'user_profile_form'){
  //debug($form_state['user']);
  $form['type_utilisateur'] = array(
    '#title' => t("S'insrire en tant que..."),
    '#type' => 'select',
    '#options' => array(
      4 => 'Enfant/Parent',
      5 => 'Représentant scolaire',
      7 => 'Citoyen',
      //6 => 'Chercheur scientifique',
      ),
    '#required' => TRUE,
    '#default_value' => isset($form_state['user']->role) ? $form_state['user']->role : "",
    );

  $form['ecole'] = array(
    '#title' => t("Nom de l'école"),
    '#type' => 'select',
    '#options' => array(
      null => 'Choisir...',
      'École Rose des Vents' => 'École Rose des Vents',
      'École des Sources' => 'École des Sources',
      'École du Rocher-Auteuil' => 'École du Rocher-Auteuil',
      'École Mont Saint-Louis' => 'École Mont Saint-Louis',
      'École Saint-Rosaire' => 'École Saint-Rosaire',
      ),
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->ecole) ? $form_state['user']->ecole : "",
    '#states' => array(
      'visible' => array(
        ':input[name="type_utilisateur"]' => array(
          array('value' => "4"),
          array('value' => "5"),
          ),
        ),
      ),
    );
  $form['prenom'] = array(
    '#title' => t("Prénom"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($form_state['user']->prenom) ? $form_state['user']->prenom : "",
    '#size'=> 30,
    );
  $form['nom_famille'] = array(
    '#title' => t("Nom de famille"),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($form_state['user']->nom_famille) ? $form_state['user']->nom_famille : "",
    '#size'=> 30,
    );
  $form['telephone'] = array(
    '#title' => t("Numéro de téléphone (optionnel)"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->telephone) ? $form_state['user']->telephone : "",
    '#size'=> 30,
    );

  $form['adresse'] = array(
    '#title' => t("Adresse"),
    '#type' => 'fieldset',
    '#required' => FALSE,
    '#size'=> 30,
    '#tree' =>FALSE,
    '#states' => array(
      'invisible' => array(
        ':input[name="type_utilisateur"]' => array('value' => "5"))),
    );
  $form['adresse']['adresse_civique'] = array(
    '#title' => t("Numéro civique et rue (ex. 145 rue Chambord)"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->adresse) ? $form_state['user']->adresse : "",
    '#size'=> 30,
    );
  $form['adresse']['adresse_appt'] = array(
    '#title' => t("Appartement (si applicable)"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->appartement) ? $form_state['user']->appartement : "",
    '#size'=> 10,
    );
  $form['adresse']['adresse_ville'] = array(
    '#title' => t("Ville"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->ville) ? $form_state['user']->ville : "",
    '#size'=> 30,
    );
  $form['adresse']['adresse_code_postal'] = array(
    '#title' => t("Code postal"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->code_postal) ? $form_state['user']->code_postal : "",
    '#size'=> 30,
    );

  $form['mangeoires'] = array(
    '#title' => t("Est-ce que vous avez une/des mangeoire(s) pour les oiseaux dans votre cour?"),
    '#type' => 'select',
    '#default_value' => isset($form_state['user']->mangeoires) ? $form_state['user']->mangeoires : "",
    '#options' => array( 
      0 => 'Non', 
      1 => 'Oui',
      ),
    '#required' => FALSE,
    );

  $form['mangeoires_nombre'] = array(
    '#title' => t("Combien de mangeoires avez-vous?"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => isset($form_state['user']->mangeoires_nombre) ? $form_state['user']->mangeoires_nombre : "",
    '#size'=> 30,
    '#states' => array(
      'visible' => array(
        ':input[name="mangeoires"]' => array('value' => "1"))),
    );

  $form['valider'] = array(
    '#title' => t("Question de vérification: compléter le nom du projet 'Des nids chez ....'"),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => '',
    '#size'=> 30,
    );
  $form['#validate'][] = 'nids_user_registration_validate';
  return $form;

}
}


// Form builder. Form ID = function name
function nids_obsnichoir_form($form, &$form_state) {
	global $user;
  	$path=drupal_get_path_alias(current_path());
  	$myObs = array();
	if(isset($_GET['id']))
  		$obsEdit = $_GET['id'];
  	if(isset($obsEdit)){
		$query = db_select('nids_nichoirs_obs', 'n');
		$query->join('nids_nichoirs', 't', 'n.nid_id = t.nid');
		$query->fields('n', array('obs_id', 'uid', 'nid_id', 'date_obs', 
		'rien_vu', 'oiseau_espece', 'oiseau_espece_autre', 'type_obs', 'type_obs_autre'))
		->fields('t', array('dncv_no', 'nom_nichoir'))
		->condition('n.obs_id', $obsEdit, '=');
		$result = $query->execute();
		
		foreach ($result as $record){
			$myObs['dncv_no'] = $record->dncv_no;
			$myObs['nom_nichoir'] = $record->nom_nichoir;
			$myObs['obs_id'] = $record->obs_id;
			$myObs['uid'] = $record->uid;
			$myObs['nid_id'] = $record->nid_id;
			$myObs['date_obs'] = $record->date_obs;
			$myObs['rien_vu'] = $record->rien_vu;
			$myObs['oiseau_espece'] = $record->oiseau_espece;
			$myObs['oiseau_espece_autre'] = $record->oiseau_espece_autre;
			$myObs['type_obs'] = $record->type_obs;
			$myObs['type_obs_autre'] = $record->type_obs_autre;
			}
		  $form['obs_id'] = array('#type' => 'hidden', '#default_value' => $obsEdit,);
		  
		$userid=$myObs['uid'];
	}
	else
   	$userid=$user->uid;

  $form['user'] = array(
    '#type' => 'hidden',
    '#default_value' => $userid,
    );

  $form['parc_ecole_check'] = array(
    '#type' => 'hidden',
    '#default_value' => $path,
    );

  $form['parc'] = array(
    '#title' => t("Pour quel parc?"),
    '#type' => 'select',
    '#options' => array(
      null => 'Choisir...',
      'Parc Beauséjour' => 'Beauséjour',
      'Parc La gare' => 'La gare',
      'Parc Mont-Saint-Louis' => 'Mont-Saint Louis',
      'Parc Mairie Saint-Anaclet' => 'Mairie Saint-Anaclet',
      'Bibliothèque Lisette-Morin' =>'Bibliothèque Lisette-Morin',
      ),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="parc_ecole_check"]' => array('value' => 'parc'),
        )
      ),
    '#ajax' => array(
      'callback' => 'ajax_parc_nichoir_callback',
      'wrapper' => 'nichoir_fs',
      'method' => 'replace',
      'effect' => 'fade',
      ),
    '#default_value' => 'Choisir',
    );


  $form['ecole'] = array(
    '#title' => t("Pour quelle école?"),
    '#type' => 'select',
    '#options' => array(
      null => 'Choisir...',
      'École Rose des Vents' => 'École Rose des Vents',
      'École des Sources' => 'École des Sources',
      'École du Rocher-Auteuil' => 'École du Rocher-Auteuil',
      'École Mont Saint-Louis' => 'École Mont Saint-Louis',
      'École Saint-Rosaire' => 'École Saint-Rosaire',
      ),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="parc_ecole_check"]' => array('value' => 'nichoir_ecole'),
        )
      ),
    '#ajax' => array(
      'callback' => 'ajax_parc_nichoir_callback',
      'wrapper' => 'nichoir_fs',
      'method' => 'replace',
      'effect' => 'fade',
      ),
    '#default_value' => 'Choisir',
    );


  global $user;
  $nidsopts=array(0 => 'Choisir....');
  if(array_key_exists('values',$form_state)) {
  	if($form_state['values']['parc_ecole_check']=='parc'){
      $nichoirs=db_select('nids_nichoirs','n')
      ->fields('n')
      ->condition('parc',$form_state['values']['parc'],'=')
      ->execute();
    } 
    else if($form_state['values']['parc_ecole_check']=='nichoir_ecole'){
      $nichoirs=db_select('nids_nichoirs','n')
      ->fields('n')
      ->condition('ecole',$form_state['values']['ecole'],'=')
      ->execute();
    } 
    else{
      $nichoirs=db_select('nids_nichoirs','n')
      ->fields('n')
      ->condition('obs_id',$myObs['obs_id'],'=')
      ->execute();
    }
  }
  else {
    $nichoirs=db_select('nids_nichoirs','n')
    ->fields('n')
    ->condition('uid',$userid,'=')
    ->execute();
  }
  if ($nichoirs->rowCount()>0){
    for ($i=1;$i<=$nichoirs->rowCount();$i++) {
      $nic=$nichoirs->fetchAssoc();
      if ($nic['dncv_no']===null)
        $nidsopts=$nidsopts + array($nic['nid']=>$nic['nom_nichoir']);
      else
        $nidsopts=$nidsopts + array($nic['nid']=>$nic['dncv_no']);
      
    }
  }

  $form['nichoir'] = array(
    '#title' => t("Pour quel nichoir?"),
    '#type' => 'select',
    '#options' => $nidsopts,
    '#required' => TRUE,
    '#prefix' => '<div id="nichoir_fs">',
    '#suffix' => '</div>',
    '#default_value' => isset($obsEdit) ? $myObs['nid_id'] : "",
    );

  $form['date'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d H:i',
    '#size' => 30,
    '#title' => "Date et heure (sur 24h) de l'observation",
    '#required' => TRUE,
    '#datepicker_options' => array('maxDate' => date('Y-m-d H:i')),
    '#default_value' => isset($obsEdit) ? $myObs['date_obs'] : "",
    );


  $form['rien_vu'] = array(
    '#title' => t("Je n'ai rien vu"),
    '#type' => 'checkbox',
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="date"]' => array('!value' => null),
        ),
      ),
    '#default_value' => isset($obsEdit) && $myObs['rien_vu'] ? true : false,
    );


  $form['espece'] = array(
    '#title' => t("Quelle espèce?"),
    '#type' => 'select',
    '#options' => array(
      null => 'Choisir...',
      'Moineau domestique' => 'Moineau domestique',
      'Hirondelle bicolore' => 'Hirondelle bicolore',
      'Mésange à tête noire' => 'Mésange à tête noire',
      'Mésange brune' => 'Mésange brune',
      'Sitelle à poitrine rousse' => 'Sitelle à poitrine rousse',
      'Merlebleu de l\'Est' => 'Merlebleu de l\'Est',
      'Inconnue' => 'Inconnue',
      'Autre' => 'Autre'
      ),
    '#required' => false,
    '#default_value' => isset($obsEdit) && !$myObs['rien_vu'] && isset($myObs['oiseau_espece_autre'])? $myObs['oiseau_espece']:'Choisir',
    '#states' => array(
      'visible' => array(
        ':input[name="rien_vu"]' => array('checked' => FALSE),
        ),
      ),
    );
	//================================================================================================================================
	// here2
	
	$form['photo'] = array(
		'#type' => 'textfield',
		'#name' => 'photo_attempt',
		'#size' => 10,
		'#value' => 'Testing...this should be the picture',
		'#prefix'=>'<td><div id="photodiv'. 2 .'">',
		'#suffix' => '</div></td></tr>',
		'#ajax' => array(
			'callback' => 'ajax_oiseau_pic_callback',
			'event' => 'mousedown',
			'wrapper' => 'oiseaux-div',
			'method' => 'replace',
			'effect' => 'fade',
			)
	);
	
	//================================================================================================================================
  $form['espece_autre'] = array(
    '#type' => 'textfield',
    '#size' => 70,
    '#title' => '<h4>'.t("Veuillez préciser l'espèce:").'</h4>',
    '#states' => array(
      'visible' => array(
        ':input[name="espece"]' => array('value' => 'Autre'),
        ),
      ),
    '#default_value' => isset($obsEdit) && !$myObs['rien_vu'] && isset($myObs['oiseau_espece'])? $myObs['oiseau_espece_autre']:'',
    );

  $form['type_obs'] = array(
    '#title' => t("Type d'observation"),
    '#type' => 'radios',
    '#size' => 50,
    '#required' => FALSE,
    '#options' => _nichoir_type_observation(),
    '#states' => array(
      'visible' => array(
        //':input[name="esp"]' => array('!value' => 'Choisir'),
        ':input[name="rien_vu"]' => array('checked' => FALSE),
        ),
      ),
       '#default_value' => isset($obsEdit) && !$myObs['rien_vu'] && isset($myObs['type_obs_autre'])? $myObs['type_obs'] : '',
    );

  $form['type_obs_autre'] = array(
    '#type' => 'textfield',
    '#size' => 70,
    '#title' => '<h4>'.t("Veuillez préciser.").'</h4>',
    '#states' => array(
      'visible' => array(
        ':input[name="type_obs"]' => array('value' => "10"),
        ':input[name="espece"]' => array('!value' => 'Choisir'),
        ),
      ),
    '#default_value' => isset($obsEdit) && !$myObs['rien_vu'] && isset($myObs['type_obs'])? $myObs['type_obs_autre'] : '',
    );

$form['submit'] = array(
  '#type' => 'submit',
  '#value' => t("Ajouter l'observation!"),
  '#states' => array(
    'visible' => array(
      ':input[name="date"]' => array('!value' => ''),
      ),
    ),
  '#suffix' => '<div style="height:100px;"></div>',
  );

$module_path = base_path().drupal_get_path('module', 'nids');

$js_files = array(
  $module_path . '/javascript/nids.jqueryui.js',
  $module_path . '/javascript/selectboxit.js',
  );
$form['#attached']['js'] = $js_files;
$form['#validate'][] = 'nids_obsnichoir_form_validate';
$form['#submit'][] = 'nids_obsnichoir_form_submit';
$form['title']['#title'] = 'Ajouter un nichoir';
return $form;
}

function nids_obscour_form($form, &$form_state) {
	global $user;
	$path=drupal_get_path_alias(current_path());
	if(isset($_GET['id']))
		$obsEdit = $_GET['id'];
	$myObsCour = array();
		if(isset($obsEdit)){
			$query = db_select('nids_oiseaux_cour', 'n');
			$query->join('nids_users', 't', 'n.uid = t.uid');
			$query->fields('n', array('obs_id', 'uid', 'ecole', 'date_obs', 
									  'rien_vu', 'duree_obs', 'oiseau_espece', 'nombre_individus'))
			->fields('t', array('uid', 'ecole'))
			->condition('n.obs_id', $obsEdit, '=');
			$result = $query->execute();
			
			foreach ($result as $record){
				$myObsCour['obs_id'] = $record->obs_id;
				$myObsCour['uid'] = $record->uid;
				$myObsCour['ecole'] = $record->ecole;
				$myObsCour['date_obs'] = $record->date_obs;
				$myObsCour['rien_vu'] = $record->rien_vu;
				$myObsCour['duree_obs'] = $record->duree_obs;
				$myObsCour['oiseau_espece'] = $record->oiseau_espece;
				$myObsCour['nombre_individus'] = $record->nombre_individus;
				
				}
			  $form['obs_id'] = array(
    		  '#type' => 'hidden',
    		  '#default_value' => $obsEdit
			  );
			}
	if(isset($obsEdit))
		$userid=$myObsCour['uid'];
   else
   	$userid=$user->uid;

  	$form['user'] = array(
   	'#type' => 'hidden',
    	'#default_value' => $userid,
    	);
  	$form['parc_ecole_check'] = array(
    	'#type' => 'hidden',
    	'#default_value' => $path,
    	);

  $form['ecole'] = array(
    '#title' => t("Nom de l'école"),
    '#type' => 'select',
    '#options' => array(
      null => 'Choisir...',
      'École Rose des Vents' => 'École Rose des Vents',
      'École des Sources' => 'École des Sources',
      'École du Rocher-Auteuil' => 'École du Rocher-Auteuil',
      'École Mont Saint-Louis' => 'École Mont Saint-Louis',
      'École Saint-Rosaire' => 'École Saint-Rosaire',
      ),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="parc_ecole_check"]' => array('value' => 'ecole_obs'),
        )
      ),
    '#default_value' => isset($obsEdit) ? $myObsCour['ecole'] : "",
    );
    
  $form['date'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'Y-m-d H:i',
    '#size' => 30,
    '#title' => "Date et heure de l'observation",
    '#datepicker_options' => array('maxDate' => date('Y-m-d H:i')),
    '#required' => TRUE,
	'#default_value' => isset($obsEdit) ? $myObsCour['date_obs'] : "",
    );

  $form['rien_vu'] = array(
    '#title' => t("Je n'ai rien vu"),
    '#type' => 'checkbox',
    '#required' => FALSE,
	'#default_value' => isset($obsEdit) ? $myObsCour['rien_vu'] : false,
    );

  $form['duree_obs'] = array(
    '#type' => 'textfield',
    '#size' => 50,
    '#title' => '<h4>'.t("Indiquer la durée de la période d'observation (en minutes).").'</h4>',
    '#required' => TRUE,
	'#default_value' => isset($obsEdit) ? $myObsCour['duree_obs'] : "",
    );

  $form['oiseau'] = array(
    '#type' => 'fieldset',
    '#title_display' => 'invisible',
    '#prefix' => '<div id="oiseaux-div"><table style="border:0px;background:white;">',
    '#suffix' => '</table></div>',
    '#tree' =>FALSE,
	'#default_value' => isset($obsEdit) ? $myObsCour['oiseau_espece'] : "",
    );

  $numoiseaux=0;
  if(array_key_exists('values',$form_state)){
    foreach ($form_state['values'] as $key => $value) {
      if (strpos($key,"espece_") !== false) {
        $numoiseaux++;
      }
    }
  }

  for ($i=0; $i<=$numoiseaux; $i++){
    $form['oiseau']['espece_'.$i] = array(
      '#title' => t("Quelle espèce?"),
      '#type' => 'select',
      '#states' => array(
        'visible' => array(
          ':input[name="rien_vu"]' => array('checked' => FALSE),
          ),
        ),
      '#options' => _observation_oiseaux_pic(true),
	  '#required' => FALSE,
	  '#multiple' => TRUE,
	  '#size' => 10,
	  '#prefix' => '<tr><td><div class="sameline">',
	  '#suffix' => '</div>',
	  '#default_value' => isset($obsEdit) ? $myObsCour['oiseau_espece'] : "",
	  );

$form['oiseau']['nombre_individus_'.$i] = array(
  '#type' => 'textfield',
  '#size' => 10,
  '#title' => '<h4>'.t("Indiquer le nombre d'individus observés (approximatif pour les grands nombres)").'</h4>',
  '#suffix' => '</div></td>',
  '#states' => array(
    'visible' => array(
      ':input[name="rien_vu"]' => array('checked' => FALSE),
      ),
    ),
  '#default_value' => isset($obsEdit) ? $myObsCour['nombre_individus'] : "",
  );
$form['oiseau']['photo_'.$i] = array(
  '#type' => 'hidden',
  '#size' => 10,
  '#prefix'=>'<td><div id="photodiv'.$i.'">',
  '#suffix' => '</div></td></tr>',
  );
//here1

}

$form['ajout_espece'] = array(
  '#type' => 'submit',
  '#value' => t("Autre espèce observée"),
  '#states' => array(
    'visible' => array(
      ':input[name="rien_vu"]' => array('checked' => FALSE),
      ),
    ),
  '#executes_submit_callback' => FALSE,
  '#ajax' => array(
    'callback' => 'ajax_ajout_oiseau_callback',
    'wrapper' => 'oiseaux-div',
    'method' => 'replace',
    'effect' => 'fade',
    ),
  );


$form['submit'] = array(
  '#type' => 'submit',
  '#value' => t("Ajouter l'observation!"),
  '#suffix' => '<div style="height:100px;"></div>',
  );

$module_path = base_path().drupal_get_path('module', 'nids');

$js_files = array(
  $module_path . '/javascript/nids.jqueryui.js',
  $module_path . '/javascript/nids.pics.js',
  $module_path . '/javascript/selectboxit.js',
  );
$form['#attached']['js'] = $js_files;
$form['#validate'][] = 'cour_form_validate';
$form['#submit'][] = 'cour_form_submit';
return $form;
}

// Form validation handler.
function nichoir_form_validate($form, &$form_state) {
	if (is_numeric($form_state['values']['hauteur'])==false & $form_state['values']['hauteur']!='')
		form_set_error('hauteur', t('Veuillez entrer un chiffre pour la hauteur!'));
		
	if ($form_state['values']['numero']=='' & $form_state['values']['nom_nichoir']=='') 
		form_set_error('numero', t('Veuillez spécifier un nom ou un numéro au nichoir!'));
		
	if ($form_state['values']['geography']=='') 
		form_set_error('geography', t('Si aucun marqueur n\'apparait sur la carte, veuillez essayer d\'utiliser le site web avec un fureteur différent (par ex. version récente de Chrome ou Firefox'));
}

// Form submit handler.
function nichoir_insert($node) {
  global $user; 
  db_insert('nids_nichoirs')->fields(array(
   'nid' => $node->nid,    
    'uid' => $node->user,
    'dncv' => $node->dncv,
    'dncv_no' => ($node->numero =='')?null:$node->numero,
    'ecole' => $node->ecole,
    'parc' => $node->parc,
    'nom_nichoir' => $node->nom_nichoir,
    'geography' => $node->geography,
    'date_installation' => $node->date_installation,
    'habitat' => $node->habitat,
    'hauteur' => ($node->hauteur =='')?null:$node->hauteur,
    'trou' => ($node->trou=='')?null:$node->trou,
    'orientation' => $node->orientation,
    ))->execute();
  drupal_set_message('Nichoir ajouté!','status');
  drupal_goto('explorer/mes_nichoirs');
}


// Form submit handler.
function nichoir_form_submit($form, &$form_state) {
if ($form_state['values']['numero']==''){
  $form_state['values']['title']=$form_state['values']['nom_nichoir'];
}
else{
  $form_state['values']['title']=$form_state['values']['numero'];
}
}

// Form validation handler.
function cour_form_validate($form, &$form_state) {
  //do validation here if necessary

}

// Form submit handler.
function cour_form_submit($form, &$form_state) {
  global $user;
  $numoiseaux=0;
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key,"espece_") !== false) {
      $numoiseaux++;
    }
  }
  for($i=0;$i<$numoiseaux;$i++)
  {
  	$exists = (array_key_exists('obs_id',$form_state['values'])) ? true : false;
  	$myArray = array(
  		'uid' => $form_state['values']['user'],
  		'ecole' => $form_state['values']['ecole'],
  		'date_obs' => $form_state['values']['date'],
  		'rien_vu' => $form_state['values']['rien_vu'],
  		'duree_obs' => ($form_state['values']['duree_obs']=='')?null:$form_state['values']['duree_obs'],
  		'oiseau_espece' => key($form_state['values']['espece_'.$i]),
  		'nombre_individus' => ($form_state['values']['nombre_individus_'.$i]=='')?null:$form_state['values']['nombre_individus_'.$i],);
  	
  	if(!$exists){
    db_insert('nids_oiseaux_cour')->fields($myArray)->execute();
    drupal_set_message('Observation ajoutée!','status');
   }
	else{
		db_update('nids_oiseaux_cour')
		->fields($myArray)
      ->condition('obs_id',$form_state['values']['obs_id'],'=')
      ->execute();
    drupal_set_message('Observation mis a jour!','status');
	}
  }
  drupal_goto('observation');
}

function nids_obsnichoir_form_validate($form, &$form_state){
  if ($form_state['values']['espece']=='' && $form_state['values']['rien_vu']==0){
    form_set_error('espece',t('Veuillez choisir une espèce ou indiquer "je n\'ai rien vu"'));
  }

}

function nids_obsnichoir_form_submit($form, &$form_state){
  $exists = 0;
  if(array_key_exists('obs_id', $form_state['values'])){
  		$obsid=$form_state['values']['obs_id'];
  
  $result = db_select('nids_nichoirs_obs', 'n')
  ->fields('n')
  ->condition('n.obs_id',$obsid,'=')
  ->execute();
  $exists = $result->rowCount();
  }
  $fieldsarray=array(
          'uid' => $form_state['values']['user'],
          'nid_id' => $form_state['values']['nichoir'],
          'date_obs' => $form_state['values']['date'],
          'rien_vu' => $form_state['values']['rien_vu'],
          'type_obs' => $form_state['values']['type_obs'],
          'type_obs_autre' => $form_state['values']['type_obs_autre'],
          'oiseau_espece' => $form_state['values']['espece'],
          'oiseau_espece_autre' => $form_state['values']['espece_autre'],
        );
        
  if(!$exists){
  		db_insert('nids_nichoirs_obs')->fields($fieldsarray)->execute();
  		drupal_set_message('Observation ajoutée!','status');
 	 	drupal_goto('observation');
  		}
  	else {
  		db_update('nids_nichoirs_obs')->fields($fieldsarray)->condition('obs_id',$obsid,'=')->execute();
  		drupal_set_message('Observation mise à jour!','status');
 	 	drupal_goto('observation');
    	}
  }

function nichoir_update($node) {
  if($node->type=='nichoir'){
    db_update('nids_nichoirs')->fields(array(
   'nid' => $node->nid,    
    'uid' => $node->user,
    'dncv' => $node->dncv,
    'dncv_no' => ($node->numero =='')?null:$node->numero,
    'ecole' => ($node->ecole=='')?null:$node->ecole,
    'parc' => ($node->parc=='')?null:$node->parc,
    'nom_nichoir' => ($node->nom_nichoir=='')?null:$node->nom_nichoir,
    'geography' => $node->geography,
    'date_installation' => $node->date_installation,
    'habitat' => $node->habitat,
    'hauteur' => ($node->hauteur =='')?null:$node->hauteur,
    'trou' => ($node->trou=='')?null:$node->trou,
    'orientation' => $node->orientation,
    ))->condition('nid', $node->nid, '=')
    ->execute();
    }
  drupal_set_message('Nichoir mis à jour!');
  drupal_goto('observation');
}

function nichoir_delete($node) {
  db_delete('nids_nichoirs')->condition('nid', $node->nid)->execute();
  db_delete('nids_nichoirs_obs')->condition('nid_id', $node->nid)->execute();
}

function nids_form_validate($form, &$form_state){

}

function ajax_oiseaux_pics_callback(){
  $photo=array();
  $oiseaux=_observation_oiseaux_pic(false);
  $oi=$_POST['oiseau'];
  $key=recursive_array_search($oi,$oiseaux['Espèces communes']);
  if($key===false){
    $key=recursive_array_search($oi,$oiseaux['Autres espèces']);
    $photo['link']=$oiseaux['Autres espèces'][$key]['pic'];
    $photo['info']=$oiseaux['Autres espèces'][$key]['url'];
  }else{
    $photo['link']=$oiseaux['Espèces communes'][$key]['pic'];
    $photo['info']=$oiseaux['Espèces communes'][$key]['url'];
  }
  drupal_json_output($photo);
}


function recursive_array_search($needle,$haystack) {
    foreach($haystack as $key=>$value) {
        $current_key=$key;
        if($needle===$value OR (is_array($value) && recursive_array_search($needle,$value) !== false)) {
            return $current_key;
        }
    }
    return false;
}

?>