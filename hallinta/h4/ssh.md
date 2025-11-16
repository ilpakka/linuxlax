# h4 Pkg-file-service

## x) Lue ja tiivistä.

1. Kirjoituksessa näytetään Saltin toimintaa SSH-palvelimelle. Teron ohjeet ovat hyödyllisiä kotitehtävissä, vaikka niitä joutuukin soveltamaan hieman distron iän ja nimen perusteella.

## a) SSHouto. 
Tavoite 1: *Lisää uusi portti, jossa SSHD kuuntelee.*
Tavoite 2: *Ensin käsin: muista näyttää, että ensin teit ja testasit muutoksen käsin. Näytä, että tilasi korjaa puutteet. Voit esimerkiksi poistaa paketin tai tehdä virheen tiedostoon käsin, sitten ajaa tilasi.*

1. Kurkataan, että mitä portteja on ensin auki.

![ssh1](src/ssh1.png)

2. Lisätään uusi portti 1337, tallennetaan tiedosto ja käynnistetään SSH uudelleen komennolla *sudo systemctl restart ssh*.

![ssh2](src/ssh2.png)

3. Luodaan tehtävälle uusi hakemisto ja kuljetaan sinne valmiiksi.

![ssh3](src/ssh3.png)

4. Rakennetaas init.sls -tiedosto soveltamalla Teron ohjeita:

![ssh4](src/ssh4.png)

5. Pkg katsoo onko openssh-server jo asennettu, file valvoo konffitiedostoa ja servicen watchi käynnistää muutostilanteista uudelleen. Eikö niin?

6. Testataan!

![ssh5](src/ssh5.png)

7. Liukastuttiin vahingossa parissa kohtaa! Nuo näkyivätkin selvästi virheilmoituksessa ja kurkkaamalla init.sls sisään on helppo löytää virheet. Pkg.installed odotti ennen jatkoa parametreille ja file.managed oli typottu muotoon file-managed. Korjataan!

![ssh6](src/ssh6.png)

8. Uusi testi paljasti pari muuta virhettä. Meiltä puuttuu tuo konffitiedosto oikeasta kohtaa, eli salttipuolelta. Myös file epäonnistui, koska aikaisempi kohta ei mennyt läpi.

![ssh7](src/ssh7.png)

9. Kopioidaan konffitiedosto oikeaan paikkaan. Korjataan myös typo *enabled* oikeaan muotoon, eli *enable*.

![ssh8](src/ssh8.png)

10. Jopas nyt on, näköjään sshd pitää vielä muuttaa muotoon ssh, jotta koko höskä toimii. Viimeinen testi?

![ssh9](src/ssh9.png)

![ssh10](src/ssh10.png)

11. Hienosti pyörii! Nyt tehdään vielä toisen tavoitteen vaatima testi, eli poistetaan paketti ja ajetaan tila uudestaan.

![ssh11](src/ssh11.png)

![ssh12](src/ssh12.png)

12. Jännä juttu. Paketin asennus onnistuu, mutta lopussa menee pieleen. Käydään katsomassa, että onko Saltin viesti totta ja saadaanko tästä jotain lisätietoja.

![ssh13](src/ssh13.png)

13. Aivan, eli tuossa on pyritty käyttämään hakemistoa /run/sshd/ jota ei kuitenkaan ole olemassa ja service.running feilaa. Luodaan se manuaalisesti ja samalla täydennetään init.sls -tiedostoon mukaan kaikki oleelliset uudistukset. Tapetaan myös vanha prosessi komennolla *sudo kill 2859*, jonka pid löytyi komennolla *ps aux | grep sshd*. Nyt meidän pitäisi välttyä ikäviltä yllätyksiltä.

![ssh14](src/ssh14.png)

![ssh15](src/ssh15.png)

![ssh16](src/ssh16.png)

14. Sormet ristissä.

![ssh17](src/ssh17.png)

15. Poisto ja viimeinen testi heti perään niin voi olla asiasta varma.

![ssh18](src/ssh18.png)

![ssh19](src/ssh19.png)

## Lähteet
- Tero Karvinen 2025. Palvelinten hallinta. Luettavissa: https://terokarvinen.com/palvelinten-hallinta
- Tero Karvinen 2018. Pkg-File-Service - Control Daemons with Salt - Change SSH Server Port. Luettavissa: https://terokarvinen.com/2018/04/03/pkg-file-service-control-daemons-with-salt-change-ssh-server-port/