
FILE* readFileCsv( const char* cy_crash_https://github.com/Assia494/Projet-Supmeca-D/securitytech_small.csv, const char*r ){
    fichier = fopen("cy_crash_tech_small.csv", "r+");
    
    if (fichier == NULL){
      printf("Ouverture du fichier impossible\n");
      printf("code d'erreur = %d \n", errno );
      printf("Message d'erreur = %s \n", strerror(errno) );
      exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
      
    }
     
fclose(fichier); 
}

















































































        
  
