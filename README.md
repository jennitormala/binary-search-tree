# binary-search-tree
A binary search tree in C.

The program reads a text file, a word at a time and removes all of the non-alphabetical characters (with the exception of apostrophes). Then it checks if the word already exists in the tree by comparing it to the words contained by the nodes in the binary search tree. In that case, the frequency of the word is incremented by one. If it isn’t in the tree, a node is created and added to the tree. After all of the words have been handled, they are added into an array. The array is Quicksorted so the words appear in alphabetical order. The program prints the 100 most frequent words in the text file.

In finnish:

Ohjelma lukee tekstitiedostosta sanan yksi kerrallaan, muuttaa kirjaimet pieniksi kirjaimiksi sekä puhdistaa sen merkeistä jotka eivät ole aakkosia (poikkeuksena heittomerkki). Sanaa haetaan binäärihakupuusta vertaamalla sitä puissa olevien solmujen sisältämiin sanihin. Jos sanaa ei vielä ole puussa, sille luodaan solmu joka lisätään puuhun. Jos sana on jo puussa, sen solmun esiintyvyyttä kasvatetaan yhdellä. Kun kaikki sanat on käyty läpi, aikaisemmin luodun binäärihakupuun solmut lisätään taulukkoon. Solmutaulukko lajitellaan sanojen esiintyvyysjärjestykseen Quicksortilla. Lopuksi tulostetaan taulukon 100 ensimmäistä solmua.

Binäärihakupuun keskimääräinen aikakompleksisuus solmun hakemisessa (search) on O(log(n)), solmun lisäämisessä (insertion) O(log(n)), poistamisessa O(log(n)) ja solmujen tulostuksessa (access) O(n). Quicksortin keskimääräinen aikakompleksisuus on O(n log(n)). Taulukon keskimääräinen aikakompleksisuus solmun lisäämisessä on O(n), poistamisessa O(n) ja solmujen tulostuksessa O(1).
