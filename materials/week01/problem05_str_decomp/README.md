Tekst zadatka: [link](https://www.algoritmi.matf.bg.ac.rs/kiaa/02/rastavljanje_niske_na_reci.html)

Ideja je objašnjena na časovima vežbi. Kod iskucati kao vežbu, za samostalni rad.

Opis rešenja:
- Uvodimo niz valid, dužine n+1, boolean tipa: valid[i] je true akko se reč word[0...i-1] može rastaviti na reči iz rečnika
- U početku, valid[0] je true - praznu reč možemo rastaviti na 0 reči iz rečnika
- Nakon toga, za svaki prefiks koji se može rastaviti na reči iz rečnika, počevši od praznog, pokušavamo da taj prefiks produžimo tako što od prve narednog karaktera pokrećemo pretragu iz korenog čvora pri čemu prelaze vršimo po karakterima iz ostatka niske. Za svaki čvor koji posetimo i koji predstavlja krajnji čvor, odgovarajuću vrednost u nizu valid postavljamo na true
- Na kraju, ukoliko je valid[n]==true onda ispisujemo DA, u suprotnom ispisujemo NE 