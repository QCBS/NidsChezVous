<?php

function _nichoir_type_observation($key = NULL) {
  $options = array(
    1 => t('Entrée ou sortie du nichoir'),
    2 => t('Apport de brindilles'),
    3 => t("Accouplement"),
    4 => t('Sons de poussins, quémande alimentaire'),
    5 => t('Alimentation des poussins par les parents (bec avec des chenilles, etc.)'),
    6 => t('Oiseau chante sur ou proche du nichoir'),
    7 => t('Il y a des oeufs dans le nid'),
    8 => t('Il y a des oisillons dans le nid'),
    9 => t('Les oiseaux semblent avoir abandonné le nid'),
    10 => t('Autre'),
    );
  return ($key) ? $options[$key] : $options;
}

function _observation_oiseaux() {
  $options = array(
        null=>"Choisir...",
        "Espèces communes"=>array( //"--- Espèces communes ---",
        "Bruant à couronne blanche"=>"Bruant à couronne blanche",
        "Bruant à gorge blanche"=>"Bruant à gorge blanche",
        "Bruant chanteur"=>"Bruant chanteur",
        "Carouge à épaulette"=>"Carouge à épaulette",
        "Chardonneret jaune"=>"Chardonneret jaune",
        "Colibri à gorge rubis"=>"Colibri à gorge rubis",
        "Corneille d'Amérique"=>"Corneille d'Amérique",
        "Durbec des sapins"=>"Durbec des sapins",
        "Étourneau sansonnet"=>"Étourneau sansonnet",
        "Geai bleu"=>"Geai bleu",
        "Hirondelle bicolore"=>"Hirondelle bicolore",
        "Jaseur d'Amérique"=>"Jaseur d'Amérique",
        "Junco ardoisé"=>"Junco ardoisé",
        "Merle d'Amérique"=>"Merle d'Amérique",
        "Mésange à tête noire"=>"Mésange à tête noire",
        "Moineau domestique"=>"Moineau domestique",
        "Paruline è croupion jaune"=>"Paruline è croupion jaune",
        "Pic chevelu"=>"Pic chevelu",
        "Quiscale bronzé"=>"Quiscale bronzé",
        "Roselin pourpré"=>"Roselin pourpré",
        "Tourterelle triste"=>"Tourterelle triste",
        ),
      "Autres espèces"=>array(//"--- Autres espèces ---",
        "Alouette hausse-col"=>"Alouette hausse-col",
        "Autour des palombes"=>"Autour des palombes",
        "Avocette d'Amérique"=>"Avocette d'Amérique",
        "Balbuzard pêcheur"=>"Balbuzard pêcheur",
        "Bécasseau semipalmé"=>"Bécasseau semipalmé",
        "Bernache cravant"=>"Bernache cravant",
        "Bernache du Canada"=>"Bernache du Canada",
        "Bruant de Lincoln"=>"Bruant de Lincoln",
        "Bruant des prés"=>"Bruant des prés",
        "Bruant familier"=>"Bruant familier",
        "Bruant fauve"=>"Bruant fauve",
        "Bruant hudsonien"=>"Bruant hudsonien",
        "Busard St-Martin"=>"Busard St-Martin",
        "Buse à queue rousse"=>"Buse à queue rousse",
        "Buse pattue"=>"Buse pattue",
        "Canard arlequin"=>"Canard arlequin",
        "Canard colvert"=>"Canard colvert",
        "Canard d'Amérique"=>"Canard d'Amérique",
        "Canard noir"=>"Canard noir",
        "Canard pilet"=>"Canard pilet",
        "Chevalier grivelé"=>"Chevalier grivelé",
        "Chevalier solitaire"=>"Chevalier solitaire",
        "Cormorant à aigrette"=>"Cormorant à aigrette",
        "Crécerelle d'Amérique"=>"Crécerelle d'Amérique",
        "Eider à duvet"=>"Eider à duvet",
        "Eider à tête grise"=>"Eider à tête grise",
        "Épervier brun"=>"Épervier brun",
        "Faucon émerillon"=>"Faucon émerillon",
        "Faucon pèlerin"=>"Faucon pèlerin",
        "Fou de Bassan"=>"Fou de Bassan",
        "Fuligule à collier"=>"Fuligule à collier",
        "Fuligule milouinan"=>"Fuligule milouinan",
        "Garrot à œil d'or"=>"Garrot à œil d'or",
        "Garrot d'Islande"=>"Garrot d'Islande",
        "Gélinotte huppé"=>"Gélinotte huppé",
        "Goéland à bec cerclé"=>"Goéland à bec cerclé",
        "Goéland arctique"=>"Goéland arctique",
        "Goéland argenté"=>"Goéland argenté",
        "Goéland bourgmestre"=>"Goéland bourgmestre",
        "Goéland marin"=>"Goéland marin",
        "Grand Chevalier"=>"Grand Chevalier",
        "Grand Corbeau"=>"Grand Corbeau",
        "Grand Harle"=>"Grand Harle",
        "Grand Heron"=>"Grand Heron",
        "Grand Pic"=>"Grand Pic",
        "Grèbe à bec bigarré"=>"Grèbe à bec bigarré",
        "Grèbe jougris"=>"Grèbe jougris",
        "Grive à dos olive"=>"Grive à dos olive",
        "Grive fauve"=>"Grive fauve",
        "Grive solitaire"=>"Grive solitaire",
        "Gros-bec errant"=>"Gros-bec errant",
        "Guillemot à miroir"=>"Guillemot à miroir",
        "Harelde kakawi"=>"Harelde kakawi",
        "Harle couronné"=>"Harle couronné",
        "Harle huppé"=>"Harle huppé",
        "Hirondelle rustique"=>"Hirondelle rustique",
        "Jaseur boréal"=>"Jaseur boréal",
        "Macareux moine"=>"Macareux moine",
        "Macreuse à bec jaune"=>"Macreuse à bec jaune",
        "Macreuse à front blanc"=>"Macreuse à front blanc",
        "Macreuse brune"=>"Macreuse brune",
        "Martin-pêcheur d'Amérique"=>"Martin-pêcheur d'Amérique",
        "Merlebleu de l'Est"=>"Merlebleu de l'Est",
        "Mésange à tête brune"=>"Mésange à tête brune",
        "Mésangeai du Canada"=>"Mésangeai du Canada",
        "Moqueur chat"=>"Moqueur chat",
        "Moucherolle tchébec"=>"Moucherolle tchébec",
        "Oie des neiges"=>"Oie des neiges",
        "Paruline à calotte noire"=>"Paruline à calotte noire",
        "Paruline à collier"=>"Paruline à collier",
        "Paruline à gorge noire"=>"Paruline à gorge noire",
        "Paruline à tête cendrée"=>"Paruline à tête cendrée",
        "Paruline bleue"=>"Paruline bleue",
        "Paruline des ruisseaux"=>"Paruline des ruisseaux",
        "Paruline flamboyant"=>"Paruline flamboyant",
        "Paruline jaune"=>"Paruline jaune",
        "Paruline masquée"=>"Paruline masquée",
        "Paruline noir et blanc"=>"Paruline noir et blanc",
        "Paruline obscur"=>"Paruline obscur",
        "Paruline tigrée"=>"Paruline tigrée",
        "Petit Garrot"=>"Petit Garrot",
        "Pic flamboyant"=>"Pic flamboyant",
        "Pic maculé"=>"Pic maculé",
        "Pic mineur"=>"Pic mineur",
        "Pie-grièche grise"=>"Pie-grièche grise",
        "Pigeon biset"=>"Pigeon biset",
        "Pipit d'Amérique"=>"Pipit d'Amérique",
        "Plectrophane des neiges"=>"Plectrophane des neiges",
        "Plectrophane lapon"=>"Plectrophane lapon",
        "Plongeon catmarin"=>"Plongeon catmarin",
        "Plongeon huard"=>"Plongeon huard",
        "Pluvier kildir"=>"Pluvier kildir",
        "Pluvier semipalmé"=>"Pluvier semipalmé",
        "Pypargue à tête blanche"=>"Pypargue à tête blanche",
        "Roitelet à couronne dorée"=>"Roitelet à couronne dorée",
        "Roitelet à couronne rubis"=>"Roitelet à couronne rubis",
        "Roselin familier"=>"Roselin familier",
        "Sarcelle à ailes bleues"=>"Sarcelle à ailes bleues",
        "Sarcelle d'été"=>"Sarcelle d'été",
        "Sarcelle d'hiver"=>"Sarcelle d'hiver",
        "Sitelle à poitrine blanche"=>"Sitelle à poitrine blanche",
        "Sitelle à poitrine rousse"=>"Sitelle à poitrine rousse",
        "Sizerin blanchâtre"=>"Sizerin blanchâtre",
        "Sizerin flammé"=>"Sizerin flammé",
        "Tarin des pins"=>"Tarin des pins",
        "Tohi à flancs roux"=>"Tohi à flancs roux",
        "Troglodyte des forêts"=>"Troglodyte des forêts",
        "Troglodyte familier"=>"Troglodyte familier",
        "Urubu à tête rouge"=>"Urubu à tête rouge",
        "Vacher à tête brune"=>"Vacher à tête brune",
        "Viréo à tête bleue"=>"Viréo à tête bleue",
        "Viréo aux yeux rouges"=>"Viréo aux yeux rouges",
        ),
    );
  return $options;
}


function nids_map($width,$height){
  drupal_add_js('http://maps.google.com/maps/api/js?sensor=false');
  drupal_add_js(base_path().drupal_get_path('module', 'nids') . '/javascript/nids.map.js');
  drupal_add_js(array('nids_mode' => 'view'), 'setting');
  $query = db_select('nids_nichoirs', 'n')->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
    'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 'habitat', 'hauteur', 'orientation'));
  $result = $query->execute();
  $output='';
  $geog=array();
  foreach($result as $n){
    $nob = db_select('nids_nichoirs_obs', 'n')->fields('n',array('type_obs','oiseau_espece'))->condition('nid_id',$n->nid,'=')->orderBy('obs_id', 'DESC')->execute()->fetchAssoc();
    if($nob['type_obs'] >= 9 || $nob['type_obs']==''){
      $ut=0; //Non Utilisé
      $sp='';
    }else{
      $ut=1; //Utilisé!
      //$sp='';
      $sp=htmlentities($nob['oiseau_espece'],ENT_QUOTES);
    }
    $iw="<div><h2><b>".(($n->dncv_no!='')?'DNCV#'.$n->dncv_no:$n->nom_nichoir)."</b></h2><div>".(($n->parc!='')?$n->parc.'<br>':'').(($n->ecole!='')?$n->ecole.'<br>':'')."Date d&#39;installation: ".$n->date_installation."</div></div><br>";
    if($ut==1){
      $iw.='<b>Utilisé!<br>'.$sp.'<img src="'.base_path().drupal_get_path('module','nids').'/images/green-check-mark.png" style="width:20px;height:20px"></b>';
    }
    $geo=json_decode($n->geography);
    $geo->features[0]->properties=array(
      'nid'=>$n->nid,
      'infowin'=>$iw,
      'utilise'=>$ut,
      );    
    $geog[]=$geo->features[0];
    //$output.="";
  }
  $arr=array(
    'type'=>'FeatureCollection',
    'features' => $geog,
    );
  $output.="<input type='hidden' name='geography' value='".json_encode($arr,JSON_UNESCAPED_SLASHES)."'>";
  $output.='<div id="map" style="width:100%;height:'.$height.'px;max-width: none;max-height:85%;"></div><br><br>';
  return $output;
}


function nids_coordinate_conversion_callback($string = "") {
  $converted_coordinates = array();
  $input = ($string) ? $string : _remove_empty_lines($_POST['coordinates']);
  $coordinates = explode("\n", $input);
  foreach($coordinates as $coordinate) {
    if(!array_key_exists($coordinate, $converted_coordinates)) {
      $converted = _make_coordinates($coordinate);
      $status = (_check_coordinate($converted)) ? 'success' : 'fail';
      $converted_coordinates[$coordinate] = array(
        'status' => $status,
        'converted' => $converted
        );
    }
  }
  drupal_json_output($converted_coordinates);
}

function _remove_empty_lines($string) {
  return preg_replace("/(^[\r\n]*|[\r\n]+)[\s\t]*[\r\n]+/", "\n", $string);
}

function _make_coordinates($point) {
  $loc = preg_replace('/\t/', '|', $point); //replace tabs with pipes
  $loc = preg_replace('/[\p{Z}\s]/u', ' ', $loc); //remove all extra spaces
  $loc = trim(preg_replace('/[^\|\d\s,;.\-NSEWO°ºdms\'"]/i', '', $loc));
  if(preg_match('/[NSEWO]/', $loc) != 0) {
    $coord = preg_split("/[\|,;]/", $loc); //split the coords by a pipe, comma, semicolon
    if (!array_key_exists(1, $coord)) { return array(null, null); }
    $coord = (preg_match('/[EWO]/', $coord[1]) != 0) ? $coord : array_reverse($coord);
    return array(_dms_to_deg(trim($coord[0])),_dms_to_deg(trim($coord[1])));
  } else {
    return preg_split("/[\|\s,;]+/",$loc); //split the coords by a pipe, space, comma, semicolon
  }
}


function _dms_to_deg($dms) {
  $dms = stripslashes($dms);
  $neg = (preg_match('/[SWO]/i', $dms) == 0) ? 1 : -1;
  $dms = preg_replace('/(^\s?-)|(\s?[NSEWO]\s?)/i','', $dms);
  $pattern = "/(\\d*\\.?\\d+)(?:[°ºd: ]+)(\\d*\\.?\\d+)*(?:['m′: ])*(\\d*\\.?\\d+)*[\"s″ ]?/i";
  $parts = preg_split($pattern, $dms, 0, PREG_SPLIT_NO_EMPTY | PREG_SPLIT_DELIM_CAPTURE);
  if (!$parts) { return; }
  // parts: 0 = degree, 1 = minutes, 2 = seconds
  $d = isset($parts[0]) ? (float)$parts[0] : 0;
  $m = isset($parts[1]) ? (float)$parts[1] : 0;
  if(strpos($dms, ".") > 1 && isset($parts[2])) {
    $m = (float)($parts[1] . '.' . $parts[2]);
    unset($parts[2]);
  }
  $s = isset($parts[2]) ? (float)$parts[2] : 0;
  $dec = ($d + ($m/60) + ($s/3600))*$neg; 
  return $dec;
}

function _check_coordinate($coord) {
  $output = false;
  if(is_numeric($coord[0])
    && is_numeric($coord[1])
    && $coord[0] <= 90 
    && $coord[0] >= -90 
    && $coord[1] <= 180 
    && $coord[1] >= -180) { $output = true; }
    return $output;
}


?>