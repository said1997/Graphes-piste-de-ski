# Graphes-piste-de-ski
ci joint les lignes de commandes de compilation du projet:

 *Etapes pour compiler
 * ouvrez le terminal a l'intérieur du dossier puis tapez les commandes suivantes :
 * gcc -c flyd.c  `sdl-config --cflags`
 * gcc flyd.o -o flyd -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
 * ./flyd
 * si cela ne marche pas vérifiez que vous avez la bibliothèque uvsqgraphics installée
 * pour installer la bibliothèque uvsq entrez dans le dossier uvsqgraphics et ouvrez le terminal dedans et tapez "make"


 
