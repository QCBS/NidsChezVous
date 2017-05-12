<?php

function my_delete()
{
	$type=$_GET['type'];
	$id = $_GET['id'];
	
	// For birds
	if($type == "observation"){
 		db_delete('nids_oiseaux_cour')->condition('obs_id',$id,'=')->execute();
  		drupal_set_message('Observation '.$id.' supprimée ','status');
 		drupal_goto('explorer');
 	}
 	// For nests
 	elseif($type == "observation_nids"){
 		db_delete('nids_nichoirs_obs')->condition('obs_id',$id,'=')->execute();
  		drupal_set_message('Observation '.$id.' supprimée ','status');
 		drupal_goto('explorer');
 	}
 	elseif($type == "nichoir") {
  		drupal_set_message('Nichoir supprimé ','status');
 		drupal_goto('explorer');
 	}
}

function my_ignored()
{
  drupal_set_message('l\'observation n\'a pas été effacée!','status');
 	drupal_goto('explorer');
}

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

function _observation_oiseaux_pic($select) {
	$myBirds = array();
	//Gets the names of birds that have already been oberved by YOU!
  global $user;
	$query1=db_select('nids_oiseaux_cour','t');
	$query1->fields('t',array('oiseau_espece'))
		   ->distinct()->condition('uid',$user->id,'=');
	$result = $query1->execute();
	$count = $result->rowCount();
	if($count > 0){
		foreach ($result as $node1) {
			$myBirds[] = array('espece' => $node1->oiseau_espece);	
		}
	}
  
  $options = array(
        null=>"Choisir...",
		"Oiseaux déjà observés" => array( //"--- Oiseaux déjà Observé ---",
			),
			
        "Espèces communes"=>array( //"--- Espèces communes ---",
          array('espece'=>'Bruant à couronne blanche',
            'url'=>'http://fr.wikipedia.org/wiki/Bruant_%C3%A0_couronne_blanche',
            'pic'=>'http://media.eol.org/content/2012/06/13/21/91267_orig.jpg'),

          array('espece'=>'Bruant à gorge blanche',
            'url'=>'http://fr.wikipedia.org/wiki/Bruant_%C3%A0_gorge_blanche',
            'pic'=>'http://media.eol.org/content/2011/12/05/07/25327_orig.jpg'),

          array('espece'=>'Bruant chanteur',
            'url'=>'http://fr.wikipedia.org/wiki/Bruant_chanteur',
            'pic'=>'http://media.eol.org/content/2012/03/25/01/72799_orig.jpg'),

          array('espece'=>'Carouge à épaulette',
            'url'=>'http://fr.wikipedia.org/wiki/Carouge_%C3%A0_%C3%A9paulettes',
            'pic'=>'http://media.eol.org/content/2012/06/13/20/07599_orig.jpg'),

          array('espece'=>'Chardonneret jaune',
            'url'=>'http://fr.wikipedia.org/wiki/Chardonneret_jaune',
            'pic'=>'http://media.eol.org/content/2012/06/13/22/63938_orig.jpg'),

          array('espece'=>'Colibri à gorge rubis',
            'url'=>'http://fr.wikipedia.org/wiki/Colibri_%C3%A0_gorge_rubis',
            'pic'=>'http://media.eol.org/content/2013/10/01/07/59593_orig.jpg'),

          array('espece'=>'Corneille d\'Amérique',
            'url'=>'http://fr.wikipedia.org/wiki/Corneille_d%27Am%C3%A9rique',
            'pic'=>'http://media.eol.org/content/2012/06/13/21/17060_orig.jpg'),

          array('espece'=>'Étourneau sansonnet',
            'url'=>'http://fr.wikipedia.org/wiki/%C3%89tourneau_sansonnet',
            'pic'=>'http://media.eol.org/content/2013/12/09/18/90796_orig.jpg'),

          array('espece'=>'Geai bleu',
            'url'=>'http://fr.wikipedia.org/wiki/Geai_bleu',
            'pic'=>'http://media.eol.org/content/2013/02/15/15/47569_orig.jpg'),

          array('espece'=>'Geai gris (Mésangeai du Canada)', 
           'url'=>'http://fr.wikipedia.org/wiki/M%C3%A9sangeai_du_Canada', 
           'pic'=>'http://media.eol.org/content/2012/06/13/22/36335_orig.jpg'),

          array('espece'=>'Hirondelle bicolore',
            'url'=>'http://fr.wikipedia.org/wiki/Hirondelle_bicolore',
            'pic'=>'http://media.eol.org/content/2012/06/13/20/11650_orig.jpg'),

          array('espece'=>'Jaseur d\'Amérique',
            'url'=>'http://fr.wikipedia.org/wiki/Jaseur_d%27Am%C3%A9rique',
            'pic'=>'http://media.eol.org/content/2012/06/13/18/17494_orig.jpg'),

          array('espece'=>'Junco ardoisé',
            'url'=>'http://fr.wikipedia.org/wiki/Junco_ardois%C3%A9',
            'pic'=>'http://media.eol.org/content/2013/10/16/16/94907_orig.jpg'),

          array('espece'=>'Merle d\'Amérique',
            'url'=>'http://fr.wikipedia.org/wiki/Merle_d%27Am%C3%A9rique',
            'pic'=>'http://media.eol.org/content/2012/06/13/18/03023_orig.jpg'),

          array('espece'=>'Mésange à tête brune', 
           'url'=>'http://fr.wikipedia.org/wiki/M%C3%A9sange_%C3%A0_t%C3%AAte_brune', 
           'pic'=>'http://media.eol.org/content/2012/06/15/08/06048_orig.jpg'),

          array('espece'=>'Mésange à tête noire',
            'url'=>'http://fr.wikipedia.org/wiki/M%C3%A9sange_%C3%A0_t%C3%AAte_noire',
            'pic'=>'http://media.eol.org/content/2009/07/24/13/07355_orig.jpg'),

          array('espece'=>'Mésangeai du Canada', 
           'url'=>'http://fr.wikipedia.org/wiki/M%C3%A9sangeai_du_Canada', 
           'pic'=>'http://media.eol.org/content/2012/06/13/22/36335_orig.jpg'),

          array('espece'=>'Moineau domestique',
            'url'=>'http://fr.wikipedia.org/wiki/Moineau_domestique',
            'pic'=>'http://media.eol.org/content/2012/10/27/14/94111_orig.jpg'),

          array('espece'=>'Paruline è croupion jaune',
            'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_croupion_jaune',
            'pic'=>'http://media.eol.org/content/2012/06/13/16/68173_orig.jpg'),

          array('espece'=>'Pic chevelu',
            'url'=>'http://fr.wikipedia.org/wiki/Pic_chevelu',
            'pic'=>'http://media.eol.org/content/2012/06/13/15/58769_orig.jpg'),

          array('espece'=>'Quiscale bronzé',
            'url'=>'http://fr.wikipedia.org/wiki/Quiscale_bronz%C3%A9',
            'pic'=>'http://media.eol.org/content/2013/06/16/15/06070_orig.jpg'),

          array('espece'=>'Roselin pourpré',
            'url'=>'http://fr.wikipedia.org/wiki/Roselin_pourpr%C3%A9',
            'pic'=>'http://media.eol.org/content/2011/11/02/01/90916_orig.jpg'),

          array('espece'=>'Tourterelle triste',
            'url'=>'http://fr.wikipedia.org/wiki/Tourterelle_triste',
            'pic'=>'http://media.eol.org/content/2012/06/13/21/86630_orig.jpg'),
          ),

      "Autres espèces"=>array( //"--- Autres espèces ---",
        array('espece'=>'Alouette hausse-col',
          'url'=>'http://fr.wikipedia.org/wiki/Alouette_hausse-col',
          'pic'=>'http://upload.wikimedia.org/wikipedia/commons/9/9a/Eremophila_alpestris2.jpg'),
        
        array('espece'=>'Autour des palombes',
          'url'=>'http://fr.wikipedia.org/wiki/Autour_des_palombes',
          'pic'=>'http://media.eol.org/content/2012/06/14/22/08095_orig.jpg'),       
        
        array('espece'=>'Avocette d\'Amérique',
          'url'=>'http://fr.wikipedia.org/wiki/Avocette_d%27Am%C3%A9rique',
          'pic'=>'http://media.eol.org/content/2011/11/02/09/94330_orig.jpg'),

        array('espece'=>'Balbuzard pêcheur',
          'url'=>'http://fr.wikipedia.org/wiki/Balbuzard_p%C3%AAcheur',
          'pic'=>'http://media.eol.org/content/2012/03/06/04/45451_orig.jpg'),

        array('espece'=>'Bécasseau semipalmé',
          'url'=>'http://fr.wikipedia.org/wiki/B%C3%A9casseau_semipalm%C3%A9',
          'pic'=>'http://media.eol.org/content/2011/11/02/16/76206_orig.jpg'),

        array('espece'=>'Bernache cravant',
          'url'=>'http://fr.wikipedia.org/wiki/Bernache_cravant',
          'pic'=>'http://media.eol.org/content/2013/07/02/05/60142_orig.jpg'),

        array('espece'=>'Bernache du Canada',
          'url'=>'http://fr.wikipedia.org/wiki/Bernache_du_Canada',
          'pic'=>'http://media.eol.org/content/2013/02/01/17/58709_orig.jpg'),

        array('espece'=>'Bruant de Lincoln',
          'url'=>'http://fr.wikipedia.org/wiki/Bruant_de_Lincoln',
          'pic'=>'http://media.eol.org/content/2013/08/23/23/00448_orig.jpg'),

        array('espece'=>'Bruant des neiges (Plectrophane des neiges)', 
         'url'=>'http://fr.wikipedia.org/wiki/Plectrophane_des_neiges', 
         'pic'=>'http://media.eol.org/content/2012/05/23/22/30605_orig.jpg'),

        array('espece'=>'Bruant des prés',
          'url'=>'http://fr.wikipedia.org/wiki/Bruant_des_pr%C3%A9s',
          'pic'=>'http://media.eol.org/content/2012/08/30/17/71660_orig.jpg'),

        array('espece'=>'Bruant familier',
          'url'=>'http://fr.wikipedia.org/wiki/Bruant_familier',
          'pic'=>'http://media.eol.org/content/2012/06/13/13/46002_orig.jpg'),

        array('espece'=>'Bruant fauve',
          'url'=>'http://fr.wikipedia.org/wiki/Bruant_fauve',
          'pic'=>'http://media.eol.org/content/2013/05/15/03/53794_orig.jpg'),

        array('espece'=>'Bruant hudsonien',
          'url'=>'http://fr.wikipedia.org/wiki/Bruant_hudsonien',
          'pic'=>'http://media.eol.org/content/2013/02/26/14/11100_orig.jpg'), 

        array('espece'=>'Busard St-Martin',
          'url'=>'http://fr.wikipedia.org/wiki/Busard_Saint-Martin',
          'pic'=>'http://media.eol.org/content/2012/06/14/23/66511_orig.jpg'),
        
        array('espece'=>'Buse à queue rousse',
          'url'=>'http://fr.wikipedia.org/wiki/Buse_%C3%A0_queue_rousse',
          'pic'=>'http://media.eol.org/content/2011/12/11/00/23661_orig.jpg'),
        
        array('espece'=>'Buse pattue',
          'url'=>'http://fr.wikipedia.org/wiki/Buse_pattue',
          'pic'=>'http://media.eol.org/content/2012/06/15/09/34914_orig.jpg'),

        array('espece'=>'Canard arlequin',
          'url'=>'http://fr.wikipedia.org/wiki/Canard_arlequin',
          'pic'=>'http://media.eol.org/content/2013/12/20/16/37296_orig.jpg'),     		  

        array('espece'=>'Canard colvert',
          'url'=>'http://fr.wikipedia.org/wiki/Canard_colvert',
          'pic'=>'http://media.eol.org/content/2012/03/06/04/11939_orig.jpg'),     		  
        
        array('espece'=>'Canard d\'Amérique',
          'url'=>'http://fr.wikipedia.org/wiki/Canard_d%27Am%C3%A9rique',
          'pic'=>'http://media.eol.org/content/2013/07/02/05/66838_orig.jpg'),

        array('espece'=>'Canard noir',
          'url'=>'http://fr.wikipedia.org/wiki/Canard_noir',
          'pic'=>'http://media.eol.org/content/2013/12/08/21/45585_orig.jpg'),

        array('espece'=>'Canard pilet',
          'url'=>'http://fr.wikipedia.org/wiki/Canard_pilet',
          'pic'=>'http://media.eol.org/content/2013/02/01/17/77692_orig.jpg'),

        array('espece'=>'Cardinal à poitrine rose',
          'url'=>'https://fr.wikipedia.org/wiki/Cardinal_%C3%A0_poitrine_rose',
          'pic'=>'https://upload.wikimedia.org/wikipedia/commons/6/60/Rose-breasted_grosbeak.jpg'),

        array('espece'=>'Chevalier grivelé',
          'url'=>'http://fr.wikipedia.org/wiki/Chevalier_grivel%C3%A9',
          'pic'=>'http://media.eol.org/content/2012/06/13/22/34953_orig.jpg'),
        
        array('espece'=>'Chevalier solitaire',
          'url'=>'http://fr.wikipedia.org/wiki/Chevalier_solitaire',
          'pic'=>'http://media.eol.org/content/2012/09/04/04/18642_orig.jpg'),

        array('espece'=>'Chouette rayée',
          'url'=>'https://fr.wikipedia.org/wiki/Chouette_ray%C3%A9e',
          'pic'=>'http://media.eol.org/content/2016/01/22/10/42962_orig.jpg'),

        array('espece'=>'Cormorant à aigrette',
          'url'=>'http://fr.wikipedia.org/wiki/Cormoran_%C3%A0_aigrettes',
          'pic'=>'http://media.eol.org/content/2012/08/30/17/57773_orig.jpg'),

        array('espece'=>'Chevalier grivelé',
          'url'=>'http://fr.wikipedia.org/wiki/Chevalier_grivel%C3%A9',
          'pic'=>'http://media.eol.org/content/2012/06/13/22/34953_orig.jpg'),

        array('espece'=>'Crécerelle d\'Amérique',
          'url'=>'http://fr.wikipedia.org/wiki/Cr%C3%A9cerelle_d%27Am%C3%A9rique',
          'pic'=>'http://media.eol.org/content/2012/01/06/01/31894_orig.jpg'),

        array('espece'=>'Durbec des sapins', 
         'url'=>'http://fr.wikipedia.org/wiki/Durbec_des_sapins', 
         'pic'=>'http://media.eol.org/content/2012/06/13/21/98614_orig.jpg'),      		  

        array('espece'=>'Eider à duvet',
          'url'=>'http://fr.wikipedia.org/wiki/Eider_%C3%A0_duvet',
          'pic'=>'http://media.eol.org/content/2012/08/07/03/31010_orig.jpg'),

        array('espece'=>'Eider à tête grise',
          'url'=>'http://fr.wikipedia.org/wiki/Eider_%C3%A0_t%C3%AAte_grise',
          'pic'=>'http://media.eol.org/content/2009/07/24/12/92001_orig.jpg'),

        array('espece'=>'Épervier brun',
          'url'=>'http://fr.wikipedia.org/wiki/%C3%89pervier_brun',
          'pic'=>'http://media.eol.org/content/2012/06/15/22/05640_orig.jpg'),

        array('espece'=>'Faucon émerillon',
          'url'=>'http://fr.wikipedia.org/wiki/Faucon_%C3%A9merillon',
          'pic'=>'http://media.eol.org/content/2012/09/04/03/69441_orig.jpg'),

        array('espece'=>'Faucon pèlerin',
          'url'=>'http://fr.wikipedia.org/wiki/Faucon_p%C3%A8lerin',
          'pic'=>'http://media.eol.org/content/2011/08/04/11/04666_orig.jpg'),

        array('espece'=>'Fou de Bassan',
          'url'=>'http://fr.wikipedia.org/wiki/Fou_de_Bassan',
          'pic'=>'http://media.eol.org/content/2012/06/13/15/69254_orig.jpg'),

        array('espece'=>'Fuligule à collier',
          'url'=>'http://fr.wikipedia.org/wiki/Fuligule_%C3%A0_collier',
          'pic'=>'http://media.eol.org/content/2013/08/23/22/89642_orig.jpg'),

        array('espece'=>'Fuligule milouinan',
          'url'=>'http://fr.wikipedia.org/wiki/Fuligule_milouinan',
          'pic'=>'http://media.eol.org/content/2012/06/13/18/06806_orig.jpg'),      		        		        		        

        array('espece'=>'Garrot à œil d\'or',
          'url'=>'http://fr.wikipedia.org/wiki/Garrot_%C3%A0_%C5%93il_d%27or',
          'pic'=>'http://media.eol.org/content/2012/05/23/07/19932_orig.jpg'),

        array('espece'=>'Garrot d\'Islande',
          'url'=>'http://fr.wikipedia.org/wiki/Garrot_d%27Islande',
          'pic'=>'http://media.eol.org/content/2012/09/15/03/46937_orig.jpg'),

        array('espece'=>'Gélinotte huppé',
          'url'=>'http://fr.wikipedia.org/wiki/Gelinotte_huppee',
          'pic'=>'http://media.eol.org/content/2011/10/06/03/55438_orig.jpg'),

        array('espece'=>'Goéland à bec cerclé',
          'url'=>'http://fr.wikipedia.org/wiki/Go%C3%A9land_%C3%A0_bec_cercl%C3%A9',
          'pic'=>'http://media.eol.org/content/2011/03/26/03/82436_orig.jpg'),      		        		        		  

        array('espece'=>'Goéland arctique',
          'url'=>'http://fr.wikipedia.org/wiki/Go%C3%A9land_arctique',
          'pic'=>'http://media.eol.org/content/2012/06/14/18/86425_orig.jpg'),

        array('espece'=>'Goéland argenté',
          'url'=>'http://fr.wikipedia.org/wiki/Go%C3%A9land_argent%C3%A9',
          'pic'=>'http://media.eol.org/content/2012/05/08/07/66173_orig.jpg'),

        array('espece'=>'Goéland bourgmestre',
          'url'=>'http://fr.wikipedia.org/wiki/Go%C3%A9land_bourgmestre',
          'pic'=>'http://media.eol.org/content/2012/06/13/18/19388_orig.jpg'),

        array('espece'=>'Goéland marin',
          'url'=>'http://fr.wikipedia.org/wiki/Go%C3%A9land_marin',
          'pic'=>'http://media.eol.org/content/2012/06/13/13/55382_orig.jpg'),

        array('espece'=>'Goglu des prés',
          'url'=>'http://fr.wikipedia.org/wiki/Goglu_des_pr%C3%A9s',
          'pic'=>'http://media.eol.org/content/2012/06/13/22/00354_orig.jpg'),

        array('espece'=>'Grand Chevalier',
          'url'=>'http://fr.wikipedia.org/wiki/Grand_Chevalier',
          'pic'=>'http://media.eol.org/content/2013/03/15/00/70583_orig.jpg'),    		  

        array('espece'=>'Grand Corbeau',
          'url'=>'http://fr.wikipedia.org/wiki/Grand_Corbeau',
          'pic'=>'http://media.eol.org/content/2012/02/04/01/25195_orig.jpg'),      		        		        		  

        array('espece'=>'Grand Harle',
          'url'=>'http://fr.wikipedia.org/wiki/Grand_Harle',
          'pic'=>'http://media.eol.org/content/2012/06/13/06/67993_orig.jpg'),

        array('espece'=>'Grand Heron',
          'url'=>'http://fr.wikipedia.org/wiki/Grand_heron',
          'pic'=>'http://media.eol.org/content/2012/06/12/22/00728_orig.jpg'),

        array('espece'=>'Grand Pic',
          'url'=>'http://fr.wikipedia.org/wiki/Grand_Pic',
          'pic'=>'http://media.eol.org/content/2013/07/02/04/78943_orig.jpg'),

        array('espece'=>'Grèbe à bec bigarré',
          'url'=>'http://fr.wikipedia.org/wiki/Gr%C3%A8be_%C3%A0_bec_bigarr%C3%A9',
          'pic'=>'http://media.eol.org/content/2012/06/13/22/99656_orig.jpg'),

        array('espece'=>'Grèbe jougris',
          'url'=>'http://fr.wikipedia.org/wiki/Gr%C3%A8be_jougris',
          'pic'=>'http://media.eol.org/content/2013/11/14/14/99392_orig.jpg'),      		  

        array('espece'=>'Grive à dos olive',
          'url'=>'http://fr.wikipedia.org/wiki/Grive_%C3%A0_dos_olive',
          'pic'=>'http://media.eol.org/content/2013/02/26/15/12685_orig.jpg'),    		  

        array('espece'=>'Grive fauve',
          'url'=>'http://fr.wikipedia.org/wiki/Grive_fauve',
          'pic'=>'http://media.eol.org/content/2014/03/05/05/15289_orig.jpg'),      		        		        		  

        array('espece'=>'Grive solitaire',
          'url'=>'http://fr.wikipedia.org/wiki/Grive_solitaire',
          'pic'=>'http://media.eol.org/content/2013/05/07/02/13364_orig.jpg'),

        array('espece'=>'Gros-bec errant',
          'url'=>'http://fr.wikipedia.org/wiki/Gros-bec_errant',
          'pic'=>'http://media.eol.org/content/2013/11/30/21/71506_orig.jpg'),

        array('espece'=>'Guillemot à miroir',
          'url'=>'http://fr.wikipedia.org/wiki/Guillemot_%C3%A0_miroir',
          'pic'=>'http://media.eol.org/content/2013/08/03/04/21785_orig.jpg'),

        array('espece'=>'Harelde kakawi',
          'url'=>'http://fr.wikipedia.org/wiki/Harelde_kakawi',
          'pic'=>'http://media.eol.org/content/2012/06/13/02/75117_orig.jpg'),

        array('espece'=>'Harle couronné',
          'url'=>'http://fr.wikipedia.org/wiki/Harle_couronn%C3%A9',
          'pic'=>'http://media.eol.org/content/2013/02/01/17/02109_orig.jpg'),		  

        array('espece'=>'Harle huppé',
          'url'=>'http://fr.wikipedia.org/wiki/Harle_hupp%C3%A9',
          'pic'=>'http://media.eol.org/content/2011/11/01/18/27086_orig.jpg'),

        array('espece'=>'Hirondelle rustique',
          'url'=>'http://fr.wikipedia.org/wiki/Hirondelle_rustique',
          'pic'=>'http://media.eol.org/content/2012/06/13/13/78901_orig.jpg'),

        array('espece'=>'Jaseur boréal',
          'url'=>'http://fr.wikipedia.org/wiki/Jaseur_bor%C3%A9al',
          'pic'=>'http://media.eol.org/content/2013/03/08/23/82017_orig.jpg'),

        array('espece'=>'Macareux moine',
          'url'=>'http://fr.wikipedia.org/wiki/Macareux_moine',
          'pic'=>'http://media.eol.org/content/2012/05/08/07/99644_orig.jpg'),

        array('espece'=>'Macreuse à bec jaune',
         'url'=>'http://fr.wikipedia.org/wiki/Macreuse_%C3%A0_bec_jaune',
         'pic'=>'http://media.eol.org/content/2013/12/18/14/71209_orig.jpg'),      		  

        array('espece'=>'Macreuse à front blanc', 
         'url'=>'http://fr.wikipedia.org/wiki/Macreuse_a_front_blanc', 
         'pic'=>'http://media.eol.org/content/2012/06/15/15/41995_orig.jpg'),

        array('espece'=>'Macreuse brune', 
         'url'=>'http://fr.wikipedia.org/wiki/Macreuse_brune', 
         'pic'=>'http://media.eol.org/content/2012/06/15/15/86513_orig.jpg'),

        array('espece'=>'Martin-pêcheur d\'Amérique', 
         'url'=>'http://fr.wikipedia.org/wiki/Martin-p%C3%AAcheur_d%27Am%C3%A9rique', 
         'pic'=>'http://media.eol.org/content/2012/03/06/04/09475_orig.jpg'),

        array('espece'=>'Merlebleu de l\'Est', 
         'url'=>'http://fr.wikipedia.org/wiki/Merlebleu_de_l%27Est', 
         'pic'=>'http://media.eol.org/content/2012/06/12/11/62423_orig.jpg'),

        array('espece'=>'Moqueur chat', 
         'url'=>'http://fr.wikipedia.org/wiki/Moqueur_chat', 
         'pic'=>'http://media.eol.org/content/2013/11/16/21/13539_orig.jpg'),

        array('espece'=>'Moqueur roux', 
         'url'=>'http://fr.wikipedia.org/wiki/Moqueur_roux', 
         'pic'=>'http://media.eol.org/content/2012/06/14/23/90633_orig.jpg'),

        array('espece'=>'Moucherolle tchébec', 
         'url'=>'http://fr.wikipedia.org/wiki/Moucherolle_tch%C3%A9bec', 
         'pic'=>'http://media.eol.org/content/2013/12/07/05/88891_orig.jpg'),

        array('espece'=>'Oie des neiges', 
         'url'=>'http://fr.wikipedia.org/wiki/Oie_des_neiges', 
         'pic'=>'http://media.eol.org/content/2013/07/02/03/46267_orig.jpg'),

        array('espece'=>'Outarde (Bernache du Canada)',
         'url'=>'http://fr.wikipedia.org/wiki/Bernache_du_Canada',
         'pic'=>'http://media.eol.org/content/2013/02/01/17/58709_orig.jpg'),

        array('espece'=>'Paruline à calotte noire', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_calotte_noire', 
         'pic'=>'http://media.eol.org/content/2011/11/02/12/25511_orig.jpg'),

        array('espece'=>'Paruline à collier', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_collier', 
         'pic'=>'http://media.eol.org/content/2013/07/02/04/81786_orig.jpg'),

        array('espece'=>'Paruline à flanc marron', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_flancs_marron', 
         'pic'=>'http://media.eol.org/content/2012/06/13/22/49288_orig.jpg'),

        array('espece'=>'Paruline à joues grises', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_joues_grises', 
         'pic'=>'http://media.eol.org/content/2011/11/01/14/26673_orig.jpg'),

        array('espece'=>'Paruline à gorge noire', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_gorge_noire', 
         'pic'=>'http://media.eol.org/content/2013/01/24/11/43258_orig.jpg'),

        array('espece'=>'Paruline à tête cendrée', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_t%C3%AAte_cendr%C3%A9e', 
         'pic'=>'http://media.eol.org/content/2012/09/15/03/62059_orig.jpg'),

        array('espece'=>'Paruline bleue', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_bleue', 
         'pic'=>'http://media.eol.org/content/2012/06/14/16/57861_orig.jpg'),

        array('espece'=>'Paruline des ruisseaux', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_des_ruisseaux', 
         'pic'=>'http://media.eol.org/content/2012/08/30/17/96689_orig.jpg'),

        array('espece'=>'Paruline flamboyant', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_flamboyante', 
         'pic'=>'http://media.eol.org/content/2013/01/25/09/30973_orig.jpg'),

        array('espece'=>'Paruline jaune', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_jaune', 
         'pic'=>'http://media.eol.org/content/2013/02/01/16/36394_orig.jpg'),

        array('espece'=>'Paruline masquée', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_masqu%C3%A9e', 
         'pic'=>'http://media.eol.org/content/2012/06/13/16/43249_orig.jpg'),

        array('espece'=>'Paruline noir et blanc', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_noir_et_blanc', 
         'pic'=>'http://media.eol.org/content/2012/11/29/16/74391_orig.jpg'),

        array('espece'=>'Paruline obscur', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_obscure', 
         'pic'=>'http://media.eol.org/content/2012/11/29/16/80091_orig.jpg'),

        array('espece'=>'Paruline tigrée', 
         'url'=>'http://fr.wikipedia.org/wiki/Paruline_tigr%C3%A9e', 
         'pic'=>'http://media.eol.org/content/2011/11/01/14/88405_orig.jpg'),

        array('espece'=>'Petit Garrot', 
         'url'=>'http://fr.wikipedia.org/wiki/Petit_Garrot', 
         'pic'=>'http://media.eol.org/content/2012/06/13/08/34526_orig.jpg'),

        array('espece'=>'Pic flamboyant', 
         'url'=>'http://fr.wikipedia.org/wiki/Pic_flamboyant', 
         'pic'=>'http://media.eol.org/content/2013/04/12/16/45748_orig.jpg'),

        array('espece'=>'Pic maculé', 
         'url'=>'http://fr.wikipedia.org/wiki/Pic_macul%C3%A9', 
         'pic'=>'http://media.eol.org/content/2013/04/29/02/27310_orig.jpg'),

        array('espece'=>'Pic mineur', 
         'url'=>'http://fr.wikipedia.org/wiki/Pic_mineur', 
         'pic'=>'http://media.eol.org/content/2012/01/13/01/06317_orig.jpg'),

        array('espece'=>'Pie-grièche grise', 
         'url'=>'http://fr.wikipedia.org/wiki/Pie-gri%C3%A8che_grise', 
         'pic'=>'http://media.eol.org/content/2012/06/19/05/74600_orig.jpg'),

        array('espece'=>'Pigeon biset', 
         'url'=>'http://fr.wikipedia.org/wiki/Pigeon_biset', 
         'pic'=>'http://media.eol.org/content/2013/03/08/13/07184_orig.jpg'),

        array('espece'=>'Pipit d\'Amérique', 
         'url'=>'http://fr.wikipedia.org/wiki/Pipit_d%27Am%C3%A9rique', 
         'pic'=>'http://media.eol.org/content/2013/07/02/03/59873_orig.jpg'),

        array('espece'=>'Plectrophane des neiges', 
         'url'=>'http://fr.wikipedia.org/wiki/Plectrophane_des_neiges', 
         'pic'=>'http://media.eol.org/content/2012/05/23/22/30605_orig.jpg'),

        array('espece'=>'Plectrophane lapon', 
         'url'=>'http://fr.wikipedia.org/wiki/Plectrophane_lapon', 
         'pic'=>'http://media.eol.org/content/2009/09/15/20/60613_orig.jpg'),

        array('espece'=>'Plongeon catmarin', 
         'url'=>'http://fr.wikipedia.org/wiki/Plongeon_catmarin', 
         'pic'=>'http://media.eol.org/content/2009/07/24/12/95547_orig.jpg'),

        array('espece'=>'Plongeon huard', 
         'url'=>'http://fr.wikipedia.org/wiki/Plongeon_huard', 
         'pic'=>'http://media.eol.org/content/2009/07/24/12/50134_orig.jpg'),

        array('espece'=>'Pluvier kildir', 
         'url'=>'http://fr.wikipedia.org/wiki/Pluvier_kildir', 
         'pic'=>'http://media.eol.org/content/2013/08/23/19/53667_orig.jpg'),

        array('espece'=>'Pluvier semipalmé', 
         'url'=>'http://fr.wikipedia.org/wiki/Pluvier_semipalm%C3%A9', 
         'pic'=>'http://media.eol.org/content/2009/07/24/12/52542_orig.jpg'),

        array('espece'=>'Pygargue à tête blanche', 
         'url'=>'http://fr.wikipedia.org/wiki/Pygargue_%C3%A0_t%C3%AAte_blanche', 
         'pic'=>'http://media.eol.org/content/2012/06/12/23/37606_orig.jpg'),

        array('espece'=>'Quiscale rouilleux', 
         'url'=>'http://fr.wikipedia.org/wiki/Quiscale_rouilleux', 
         'pic'=>'http://media.eol.org/content/2013/02/26/15/55276_orig.jpg'),

        array('espece'=>'Roitelet à couronne dorée', 
         'url'=>'http://fr.wikipedia.org/wiki/Roitelet_%C3%A0_couronne_dor%C3%A9e', 
         'pic'=>'http://media.eol.org/content/2012/11/13/20/88799_orig.jpg'),

        array('espece'=>'Roitelet à couronne rubis', 
         'url'=>'http://fr.wikipedia.org/wiki/Roitelet_%C3%A0_couronne_rubis', 
         'pic'=>'http://media.eol.org/content/2012/06/14/18/93663_orig.jpg'),

        array('espece'=>'Roselin familier', 
         'url'=>'http://fr.wikipedia.org/wiki/Roselin_familier', 
         'pic'=>'http://media.eol.org/content/2013/10/16/16/65016_orig.jpg'),

        array('espece'=>'Sarcelle à ailes bleues', 
         'url'=>'http://fr.wikipedia.org/wiki/Sarcelle_%C3%A0_ailes_bleues', 
         'pic'=>'http://media.eol.org/content/2012/06/14/17/64740_orig.jpg'),

        array('espece'=>'Sarcelle d\'été', 
         'url'=>'http://fr.wikipedia.org/wiki/Sarcelle_d%27%C3%A9t%C3%A9', 
         'pic'=>'http://media.eol.org/content/2012/08/30/15/38447_orig.jpg'),

        array('espece'=>'Sarcelle d\'hiver', 
         'url'=>'http://fr.wikipedia.org/wiki/Sarcelle_d%27hiver', 
         'pic'=>'http://media.eol.org/content/2012/11/04/08/35791_orig.jpg'),

        array('espece'=>'Sitelle à poitrine blanche', 
         'url'=>'http://fr.wikipedia.org/wiki/Sittelle_%C3%A0_poitrine_blanche', 
         'pic'=>'http://media.eol.org/content/2013/01/30/10/18727_orig.jpg'),

        array('espece'=>'Sitelle à poitrine rousse', 
         'url'=>'http://fr.wikipedia.org/wiki/Sitelle_%C3%A0_poitrine_rousse', 
         'pic'=>'http://media.eol.org/content/2011/11/01/14/17486_orig.jpg'),

        array('espece'=>'Sizerin blanchâtre', 
         'url'=>'http://fr.wikipedia.org/wiki/Sizerin_blanch%C3%A2tre', 
         'pic'=>'http://media.eol.org/content/2013/12/08/16/56216_orig.jpg'),

        array('espece'=>'Sizerin flammé', 
         'url'=>'http://fr.wikipedia.org/wiki/Sizerin_flamm%C3%A9', 
         'pic'=>'http://media.eol.org/content/2012/06/13/02/97539_orig.jpg'),

        array('espece'=>'Tarin des pins', 
         'url'=>'http://fr.wikipedia.org/wiki/Tarin_des_pins', 
         'pic'=>'http://media.eol.org/content/2013/05/15/03/82329_orig.jpg'),

        array('espece'=>'Tohi à flancs roux', 
         'url'=>'http://fr.wikipedia.org/wiki/Tohi_%C3%A0_flancs_roux', 
         'pic'=>'http://media.eol.org/content/2013/07/02/03/67023_orig.jpg'),

        array('espece'=>'Troglodyte des forêts', 
         'url'=>'http://www.ec.gc.ca/soc-sbc/oiseau-bird-eng.aspx?sY=2011&sL=f&sM=p1&sB=WIWR', 
         'pic'=>'http://media.eol.org/content/2012/06/13/14/04360_orig.jpg'),

        array('espece'=>'Troglodyte familier', 
         'url'=>'http://fr.wikipedia.org/wiki/Troglodyte_familier', 
         'pic'=>'http://media.eol.org/content/2013/10/26/03/10827_orig.jpg'),

        array('espece'=>'Tyran tritri', 
         'url'=>'http://fr.wikipedia.org/wiki/Tyran_tritri', 
         'pic'=>'http://media.eol.org/content/2012/06/13/22/90940_orig.jpg'),

        array('espece'=>'Urubu à tête rouge', 
         'url'=>'http://fr.wikipedia.org/wiki/Urubu_%C3%A0_t%C3%AAte_rouge', 
         'pic'=>'http://media.eol.org/content/2009/09/15/18/83681_orig.jpg'),

        array('espece'=>'Vacher à tête brune', 
         'url'=>'http://fr.wikipedia.org/wiki/Vacher_%C3%A0_t%C3%AAte_brune', 
         'pic'=>'http://media.eol.org/content/2010/12/10/02/30175_orig.jpg'),

        array('espece'=>'Viréo à tête bleue', 
         'url'=>'http://fr.wikipedia.org/wiki/Vir%C3%A9o_%C3%A0_t%C3%AAte_bleue', 
         'pic'=>'http://media.eol.org/content/2013/04/26/08/51161_orig.jpg'),

        array('espece'=>'Viréo aux yeux rouges', 
         'url'=>'http://fr.wikipedia.org/wiki/Vir%C3%A9o_aux_yeux_rouges', 
         'pic'=>'http://media.eol.org/content/2013/07/02/04/48770_orig.jpg'),
      ),
    );
	

    if ($select==true) {
      if ($count > 0){
      $options= birds_already_observed($options, $myBirds);
      return array('Oiseaux déjà observés'=>simplify_pic_array($options['Oiseaux déjà observés']),
				           'Espèces communes'=>simplify_pic_array($options['Espèces communes']),
                   'Autres espèces'=>simplify_pic_array($options['Autres espèces']),
          );
      } else {
      return array('Espèces communes'=>simplify_pic_array($options['Espèces communes']),
                   'Autres espèces'=>simplify_pic_array($options['Autres espèces']),
          );        
      }
    } else {
      return $options;
    }
}

function simplify_pic_array($options){
  $opts=array();
  foreach($options as $o){
    if (preg_match('!\(([^\)]+)\)!', $o['espece'],$t)) { 
      $op=array($t[1]=>$o['espece']);
    }else{
      $op=array($o['espece']=>$o['espece']);
    }
    $opts=$opts+$op;
  }
  return $opts;
}

function birds_already_observed($options, $myBirds){
		foreach($options['Espèces communes']  as $key=>$value){
			for($i = 0; $i < count($myBirds); $i++){
				if($value['espece'] == $myBirds[$i]['espece']){
					$options['Oiseaux déjà observés'][$i] =
					array('espece'=> $value['espece'], 
						  'url'=> $value['url'],
						  'pic'=> $value['pic']);
						  unset($options['Espèces communes'][$key]);
				}
			}
		}
		foreach($options['Autres espèces']  as $key=>$value){
			for($i = 0; $i < count($myBirds); $i++){
				if($value['espece'] == $myBirds[$i]['espece']){
					$options['Oiseaux déjà observés'][$i] =
					array('espece'=> $value['espece'], 
						  'url'=> $value['url'],
						  'pic'=> $value['pic']);
						  unset($options['Autres espèces'][$key]);
				}
			}
		}
	return $options;
}

function nids_map($width,$height){
  drupal_add_js('http://maps.google.com/maps/api/js?sensor=false');
  drupal_add_js(base_path().drupal_get_path('module', 'nids') . '/javascript/nids.map.js');
  drupal_add_js(array('nids_mode' => 'view'), 'setting');
  $query = db_select('nids_nichoirs', 'n')->fields('n',array('nid', 'uid', 'dncv', 'dncv_no', 
    'nom_nichoir', 'parc', 'ecole', 'geography', 'date_installation', 'habitat', 'hauteur', 'orientation','type_nichoir'));
  $result = $query->execute();
  $output='';
  $geogi=array();
  $geogu=array();
  foreach($result as $n){
    if(1){  //BASED ON LAST OBSERVATIION RE-ENABLE IN 2015!!
        $nob = db_select('nids_nichoirs_obs', 'n')->fields('n',array('type_obs','oiseau_espece'))->condition('nid_id',$n->nid,'=')->condition('date_obs','2016-01-01','>')->orderBy('obs_id', 'DESC')->execute()->fetchAssoc();
    }else{
        $nob = db_query('SELECT min(n.type_obs) as type_obs FROM nids_nichoirs_obs n WHERE n.nid_id=:nid',array(':nid' => $n->nid))->fetchAssoc();
    }
    if($nob['type_obs'] >= 9 || $nob['type_obs']==''){
      $ut=0; //Non Utilisé
      $sp='';
    }else{
      $ut=1; //Utilisé!
      //$sp='';
      $sp=htmlentities($nob['oiseau_espece'],ENT_QUOTES);
    }
    $iw="<div><h2><b>".(($n->dncv_no!='')?$n->type_nichoir.'#'.$n->dncv_no:$n->nom_nichoir)."</b></h2><div>".(($n->parc!='')?$n->parc.'<br>':'').(($n->ecole!='')?$n->ecole.'<br>':'')."Date d&#39;installation: ".$n->date_installation."</div></div><br>";
    if($ut==1){
      $iw.='<b>Utilisé!<br>'.$sp.'<img src="'.base_path().drupal_get_path('module','nids').'/images/green-check-mark.png" style="width:20px;height:20px"></b>';
    }
    $geo=json_decode($n->geography);
    $geo->features[0]->properties=array(
      'nid'=>$n->nid,
      'infowin'=>$iw,
      'utilise'=>$ut,
      );
    if($ut==1){ //put used at end
    	$geogu[]=$geo->features[0];
    }else{
    	$geogi[]=$geo->features[0];
    }
    //$output.=""
  }
  $geog=array_merge($geogi,$geogu);  
  $arr=array(
    'type'=>'FeatureCollection',
    'features' => $geog,
    );
  $output.="<input type='hidden' name='geography' value='".json_encode($arr,JSON_UNESCAPED_SLASHES)."'>";
  $output.='<div id="map" style="width:100%;height:'.$height.'px;max-width: none;max-height:85%;"></div><br><br>';
  return $output;
}

function cmp($a, $b) {
   //return $a[0]->properties['utilise'] - $a[0]->properties['utilise'];
 return strcmp($a[0]->properties['utilise'],$b[0]->properties['utilise']);
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

function charts_queries_sp_frequentes(){

  if($_POST['chart']=='indiv'){
    $q=db_query("SELECT oiseau_espece, date_trunc('week', date_obs::date) AS semaine, sum(nombre_individus) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece IN(SELECT oiseau_espece FROM nids_oiseaux_cour WHERE oiseau_espece IS NOT NULL AND oiseau_espece != '' AND nombre_individus IS NOT NULL  AND extract(YEAR from date_obs::date)=date_part('year', now())  GROUP BY oiseau_espece ORDER BY sum(nombre_individus) DESC LIMIT 10) AND extract(YEAR from date_obs::date)=date_part('year', now()) GROUP BY semaine, oiseau_espece ORDER BY oiseau_espece")->fetchAll();
  }else if ($_POST['chart']=='obs'){
    $q=db_query("SELECT oiseau_espece, date_trunc('week', date_obs::date) AS semaine, count(*) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece IN(SELECT oiseau_espece FROM nids_oiseaux_cour WHERE oiseau_espece IS NOT NULL AND oiseau_espece != '' AND extract(YEAR from date_obs::date)=date_part('year', now()) GROUP BY oiseau_espece ORDER BY count(*) DESC LIMIT 10) AND extract(YEAR from date_obs::date)=date_part('year', now()) GROUP BY semaine, oiseau_espece ORDER BY oiseau_espece")->fetchAll();
  }else if ($_POST['chart']=='bar_freq'){
    $q=db_query("SELECT oiseau_espece, count(*) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece IN(SELECT oiseau_espece FROM nids_oiseaux_cour WHERE oiseau_espece IS NOT NULL AND oiseau_espece != '' AND nombre_individus IS NOT NULL GROUP BY oiseau_espece ORDER BY sum(nombre_individus) DESC LIMIT 10) GROUP BY oiseau_espece ORDER BY nbre DESC")->fetchAll();    
  }else{
    $q=db_query("SELECT oiseau_espece, sum(nombre_individus) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece IN(SELECT oiseau_espece FROM nids_oiseaux_cour WHERE oiseau_espece IS NOT NULL AND oiseau_espece != '' AND nombre_individus IS NOT NULL GROUP BY oiseau_espece ORDER BY sum(nombre_individus) DESC LIMIT 10) GROUP BY oiseau_espece ORDER BY nbre DESC")->fetchAll();   
  }
  $result = array();
 
 if($_POST['chart']=='indiv' || $_POST['chart']=='obs'){
    $oe='';
    foreach($q as $s) {
      if($s->nbre != NULL){
        if($s->oiseau_espece!=$oe) {
            $result[]['name'] = $s->oiseau_espece;
            end($result);
            $key = key($result);
        }
        $result[$key]['data'][] = array($s->semaine,$s->nbre);
        $oe=$s->oiseau_espece;
      }
    }
  }else{
      $result=$q;
  }
  drupal_json_output($result);
}

function charts_queries_diversite(){
  $q=db_query("SELECT date_trunc('week', date_obs::date) AS semaine, count(DISTINCT oiseau_espece) as nbre FROM nids_oiseaux_cour GROUP BY semaine ORDER BY semaine")->fetchAll();
  $result = array();
  $result[0]['name'] = 'Nombre d\'espèces';
  foreach($q as $s) {
    $result[0]['data'][] = array($s->semaine,$s->nbre);
  }

  $q=db_query("SELECT date_trunc('week', date_obs::date) AS semaine, count(DISTINCT uid) as nbre FROM nids_oiseaux_cour GROUP BY semaine ORDER BY semaine")->fetchAll();
  $result[1]['name'] = 'Nombre de participants';
  foreach($q as $s) {
    $result[1]['data'][] = array($s->semaine,$s->nbre);
  }
  drupal_json_output($result);
}


function charts_queries_ma_diversite(){
  global $user;
  $uid=$user->uid;
  //$uid=74;
if($_POST['graph']=="especes"){
  $q=db_query("SELECT date_trunc('week', date_obs::date) AS semaine, count(DISTINCT oiseau_espece) as nbre FROM nids_oiseaux_cour WHERE uid=$uid GROUP BY semaine ORDER BY semaine")->fetchAll();
  $result = array();
  $result[0]['name'] = 'Nombre d\'espèces';
  foreach($q as $s) {
    $result[0]['data'][] = array($s->semaine,$s->nbre);
  }
}else{
  $q=db_query("SELECT date_trunc('week', a.date_obs::date) as semaine, sum(a.duree_obs) as nbre FROM (SELECT DISTINCT date_obs, duree_obs FROM nids_oiseaux_cour WHERE uid=$uid) a GROUP BY semaine ORDER BY semaine")->fetchAll();
  $result[0]['name'] = 'Nombre d\'heures';
  foreach($q as $s) {
    $result[0]['data'][] = array($s->semaine,$s->nbre);
  }
}
  drupal_json_output($result);
}

function charts_queries_par_sp(){

$sp=pg_escape_string($_POST['espece']);
$an=$_POST['annee'];
if($_POST['type_graph']=='indiv'){
  $q=db_query("SELECT oiseau_espece, date_trunc('week', date_obs::date)::date AS semaine, sum(nombre_individus) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece='$sp' AND extract(YEAR from date_obs::date)=".$an." GROUP BY oiseau_espece,semaine ORDER BY semaine")->fetchAll();
}else{
  $q=db_query("SELECT oiseau_espece, date_trunc('week', date_obs::date)::date AS semaine, count(*) as nbre FROM nids_oiseaux_cour WHERE oiseau_espece='$sp' AND extract(YEAR from date_obs::date)=".$an." GROUP BY oiseau_espece,semaine ORDER BY semaine")->fetchAll();
}
  $result = array();
  $oe='';
  foreach($q as $s) {
    if($s->oiseau_espece!=$oe) {
        $result[]['name'] = $s->oiseau_espece;
        end($result);
        $key = key($result);
    }
    $result[$key]['data'][] = array($s->semaine,$s->nbre);
    $oe=$s->oiseau_espece;
  }
  drupal_json_output($result);
}

?>

