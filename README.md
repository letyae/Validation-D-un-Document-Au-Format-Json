# Validation-D-un-Document-Au-Format-Json
A partir d'un schémas prédéfinis on vérifie si les données dans un document au format Json concorde avec celui du schémas


Il est aussi nécessaire de télécharger les fichiers   "cJSON.h",  "cJSON_Utils.h" qui contiennent des fonctions de gestion de donnée Json (Parser et autres) https://github.com/DaveGamble/cJSON 

La fonction Main.c est lancé avec deux fichiers en entrée en argument: le schémas et le doc. contenant la donnée. Ils sont parsés puis la fonction   compare vérifie chaque donnée par rapport au type prévue dans le schémas. 
