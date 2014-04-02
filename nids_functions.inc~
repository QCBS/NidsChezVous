<?php

function observation_delete()
{
	$obs_id = $_GET['obs_id'];
 	db_delete('nids_oiseaux_cour')->condition('obs_id',$obs_id,'=')->execute();
  	drupal_set_message('Observation '. $_GET['obs_id'] .' supprimée ','status');
 	drupal_goto('explorer/observation_oiseaux');
}

function observation_ignored()
{
  	drupal_set_message('Observation demeuré!','status');
 	drupal_goto('explorer/observation_oiseaux');
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
        "Mésange à tête brune"=>"Mésange à tête brune",
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

function _observation_oiseaux_pic() {
$options = array(
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
      
      "Autres espèces"=>array(//"--- Autres espèces ---",
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

         array('espece'=>'Chevalier grivelé',
      		  'url'=>'http://fr.wikipedia.org/wiki/Chevalier_grivel%C3%A9',
      		  'pic'=>'http://media.eol.org/content/2012/06/13/22/34953_orig.jpg'),
        
         array('espece'=>'Chevalier solitaire',
      		  'url'=>'http://fr.wikipedia.org/wiki/Chevalier_solitaire',
      		  'pic'=>'http://media.eol.org/content/2012/09/04/04/18642_orig.jpg'),

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

			array('espece'=>'Mésangeai du Canada', 
		  			'url'=>'http://fr.wikipedia.org/wiki/M%C3%A9sangeai_du_Canada', 
		  			'pic'=>'http://media.eol.org/content/2012/06/13/22/36335_orig.jpg'),
		  
			array('espece'=>'Moqueur chat', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Moqueur_chat', 
		  			'pic'=>'http://media.eol.org/content/2013/11/16/21/13539_orig.jpg'),

			array('espece'=>'Moucherolle tchébec', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Moucherolle_tch%C3%A9bec', 
		  			'pic'=>'http://media.eol.org/content/2013/12/07/05/88891_orig.jpg'),
		  
			array('espece'=>'Oie des neiges', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Oie_des_neiges', 
		  			'pic'=>'http://media.eol.org/content/2013/07/02/03/46267_orig.jpg'),
		  
			array('espece'=>'Paruline à calotte noire', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_calotte_noire', 
		  			'pic'=>'http://media.eol.org/content/2011/11/02/12/25511_orig.jpg'),
		  
			array('espece'=>'Paruline à collier', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Paruline_%C3%A0_collier', 
		  			'pic'=>'http://media.eol.org/content/2013/07/02/04/81786_orig.jpg'),

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
		  
		  //Spelling error confirm with Guillaume
			array('espece'=>'Pypargue à tête blanche', 
		  			'url'=>'http://fr.wikipedia.org/wiki/Pygargue_%C3%A0_t%C3%AAte_blanche', 
		  			'pic'=>'http://media.eol.org/content/2012/06/12/23/37606_orig.jpg'),
		  
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