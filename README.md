- il me faut aussi une fontion buffer pour
  check les resultats de mes tests

- trier un tab est toujours plus per qu'une liste chainer

- afficher les dossiers de mon directory dans l'orde ascii.
- c'est ici que je fais le trie, mais je ne sais pas si je le 
  fais dans l'ordre asscii ? we will see ! 

- afficher les option de ll dans le meme ordre.

- en construisant ma liste chainee, 
  je fais un tab qui contient toute les entree pour 
  mes datas, et il
  
- pour les colomn, je def la taille max
  et je fais des calcule pour que ca fit dedans
  avec le bon nombres de colomnes
  
- je list tout le contenu du dossier et je 
  get toute les informations qu'il y a dedans
  
- a part la premiere lecture, je ne vais jamais en arriere

- -r > inverser l'ordre de trie pour le t ou le normal

- manage les err comme le vrai ls

- 1 print et trier le contenue de mon directory ?
  le mettre dans une liste chainer et un tab ?



- add acl / att etendue
- add color
- add colunm
- add tree ?
- add d > afficher les dossier comme les fichiers
- human // ?

l'option l est chiante pour:



1: prendre un directory et le lister entierement
   mettre dans un tab ce qu'il y a dans ma directory
   en comptant 2 fois les choses dedans + malloc.
   
2: trier dans avec la fonction donner en param ce que j'ai dedans
   - fonction pour manager les tab
   - dernier trucs de mon tab dois etre vide pour stop ou 
     c'est un ptr, mettre a null suffit. 

comment j'affiche les symlink ? 


pour le all je dois prendre la taille de tout les block enfant.
sb.st_blocks

commande pour la taille des path : 

ls -R | sed -n -e '/^\.\//p' > toto.txt
awk 'length>300' toto.txt


# breaking new 
- la size max d'un file est de 255 c ' '
- la size maxe de mon path est de PATH_MAX. pas besoin de mettre plus.

# faire une refacto du code
faire la fonction de test qui init la recursivite
lancer la recursivite
et voila ! :)

- faire la recursivite !
    - 1

- pour le moment je compte le nb d'element pour allouer mon tab, ensuite je ferai le print
- ajouter les trie
- implemeter tout les trie possbile
- la couleur c'est style ! 
- le truc des groupes user aussi c'est style
- je suis pas sur qu'avec mes buffer ca soit bullet proof, /a voir avec les tests
- ajouter les colomne ?
- faire l'affichage en fonction des options
- faire l'input, la boucle sur les arguments,
  
- faire les tests du truc de test
- faire regarder les best projets de ce ls
- 

- if the file has 3 stuff, no need to use a sorting

// 1 build_sorted_array
    X - compte le nb d'element et init le tab avec 
    X - loop sur le tab d'element et fill le tab
j
1 -> faire le parcing et faire mettre les arguments en ordre. 
2 -> tester avec les -.
3 -> coder un trie a bulle pour mon array.
3 -> apprendre comment marche 42 files checker en l'utiliser pour faire mes corrections ?. 









