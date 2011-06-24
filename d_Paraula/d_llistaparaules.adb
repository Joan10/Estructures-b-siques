with d_paraula, ada.integer_text_io, ada.text_io;
use d_paraula, ada.integer_text_io, ada.text_io;
package body d_llistaparaules is

   procedure LlistaBuida(L: out LlistaParaules) is
   begin
      L.Primer  := null;
      L.Darrer := null;
   end LlistaBuida;

   procedure Posa(L: in out LlistaParaules; P: in Paraula) is
      --Posa afegeix la paraula al final de la llista.

      nodeLlista: ptr_nLlista;
   begin
      if L.Primer = null and L.Darrer = null then --Si la llista era buida...
         L.Primer := new nLlista;
         L.Primer.all.succ := null; L.Primer.all.pred := null;
         L.Primer.all.P := P;
         L.Darrer := L.Primer;
      else

         --Cream el nou node
         nodeLlista := new nLlista;
         nodeLlista.all.succ := null;
	 nodeLlista.all.P := P;
         nodeLlista.all.pred := L.Darrer;

         --Feim els canvis adients en la llista per donar cabuda al nou node
         L.Darrer.all.succ := nodeLlista;
         L.Darrer := nodeLlista;

      end if;
   end Posa;



   procedure Ordena(L: in out LlistaParaules) is
      --Procediment que ordena la llista de paraules passada.

      subtype c_index is character range character'val(32)..'z';
      --subtipus emprat per indexar el vector.
      --Empram aquest i no el caràcter per si ens embullam amb els indexos que el compilador ens avisi.

      type d_Cistella is array (c_index) of LlistaParaules;
      --Declaram el tipus cistella, que és un vector indexat per caracters.

	Cistella: d_Cistella;
	l_max:integer;

      function max_longitud(L: in LlistaParaules) return integer is
      --funció que retorna la longitud màxima de les paraules d'una llista.
     	 Max,n: integer;
     	 nP:Ptr_nLlista;
      begin
         nP:=L.Primer; --P pren el valor de la primera paraula de la llista.
         Max := 0;
         while (nP/=null) loop
            n:=d_paraula.llargaria(nP.p);
            if (n>Max) then Max:=n; end if;
            nP:=nP.succ;
         end loop;

         return Max;

      end max_longitud;

      nP:Ptr_nLlista;
      c: character; --caracter que servirà per indexar

      procedure treu_de_cistella(nP: in out Ptr_nLlista; L_act: in out LlistaParaules) is
         --Per ajustar els punters per treure un element de la cistella ho he decidit separar
         --per fer-ho més net visualment. Aquest procediment simplement ajusta els punters per eliminar
         --l'element de la cistella que ens sobra.
      begin
         --Tenim quatre casos que cal tenir en compte:

         --El node és únic, per tant la llista quedarà buida.
         if nP.pred = null and nP.succ = null then
            L_act.Primer := null;
            L_act.Darrer := null;

         --El node és el primer, per tant ajustam els punters.
         elsif nP.pred = null and nP.succ /= null  then
            L_act.Primer := nP.succ;
            L_act.Primer.pred := null;

         --El node és el darrer, per tant ajustam els punters.
         elsif nP.succ = null and nP.pred /= null then
            L_act.Darrer := nP.pred;
            L_act.Darrer.succ := null;
         else
        --El node està enmig.
            nP.pred.succ := nP.succ;
            nP.succ.pred := nP.pred;
         end if;

      end treu_de_cistella;

      procedure GeneraLlistaOrdenada(L:in out LlistaParaules; Cistella: in out d_Cistella) is
         -- Genera llista ordenada crea, donat un vector de cistelles, una LlistaParaules on el primer element és el primer element
         -- de la primera cistella del vector de cistelles que és plena i el darrer n'és el darrer element de la darrera cistella que és plena
         -- Evidentment, les cistelles intermitges es connecten entre sí per generar una llista nova.
         -- Això he decidit fer-ho així per evitar emprar més memòria de la necessària i reutilitzar la emprada per les cistelles.

         i: c_index := c_index'first;
         succ_i: c_index;

         function proximNoBuit(c: in c_index; Cistella: in d_Cistella) return c_index is
            -- Aquesta funció retorna, donat un caràcter índex i una cistella, el proper valor del caràcter
            -- pel qual la cistella que indexa al vector de cistelles no és buida. En cas que no n'hi hagi cap
            -- retornarà el mateix valor que ha entrat. En aquest cas també s'inclou la possibilitat que s'entri una
            -- 'z', i per tant no és possible que hi hagi un altre valor de c (diferent de l'inicial) tal que Cistella(c) no sigui buida.

            i: c_index := c;
         begin

            if i = c_index'last then  return i; end if;

	    i := c_index'succ(i);
            while esBuida(Cistella(i)) and i<c_index'last loop
               i := c_index'succ(i);
            end loop;

            if i = c_index'last then
            	if esBuida(Cistella(i)) then
              	 return c;
            	end if;
            end if;

            return i;
         end proximNoBuit;

      begin

         i := proximNoBuit(i, Cistella);
         succ_i := proximNoBuit(i, Cistella);

         L.Primer := Cistella(i).Primer;

         while i /= succ_i loop
            --Anam interant fins que ja no queden més cistelles. És a dir, en fer proximNoBuit, si succ_i retorna el mateix valor
            --perque ja no queden més cistelles del vector que visitar, succ_i = i (per l'assignació de baix) per tant el valor
            --de i serà igual a succ_i per tant sortirem del bucle. Podria passar. però, que succ_i fós c_index'last(generalment'z')
            --En aquest cas la funció retornarà també el mateix valor passat.
            Cistella(i).Darrer.succ := Cistella(succ_i).Primer;
            Cistella(succ_i).Primer.pred := Cistella(i).Darrer;

            i := succ_i;
            succ_i := proximNoBuit(succ_i, Cistella);
         end loop;


         L.Darrer := Cistella(succ_i).Darrer;

      end GeneraLlistaOrdenada;

   begin
     np:=L.Primer;
     l_max := max_longitud(L); --longitud màxima.

     while (nP/=null) loop
         c:=d_paraula.charPos(nP.P,l_max);
         Posa(Cistella(c), nP.P);
         nP:=nP.succ;
     end loop;

     for n in reverse 1..l_max-1 loop
         --Assignam a la cistella que processam la cistella del valor anterior a 'a'.
         for i in c_index loop --i és caracter que indexarà el vector.
            nP:=Cistella(i).Primer;
            while (np /= null) loop
               c:=d_paraula.charPos(nP.P,n); --Per cada paraula de la cistella agafam el valor del caracter de la posició n.
               if (c /= i) then --comprovam que el node no estigui marcat i que el caràcter sigui diferent.
                  Posa(Cistella(c),nP.P);
                  treu_de_cistella(nP, Cistella(i));
               end if;

               nP:=nP.succ;
            end loop;
      	 end loop;
     end loop;
     GeneraLlistaOrdenada(L,Cistella);
 end Ordena;

   procedure Escriu(L: in LlistaParaules; E: e_Ordre) is
   --Escriu una llista de paraules amb l'ordre passat.

      p: Ptr_nLLista;
   begin
      if L.Primer = null and L.Darrer = null then raise error_LlistaBuida; end if;
      if E = Ascendent then p:=L.Primer; else p:=L.Darrer; end if;
      while p /= null loop
         d_Paraula.put(p.all.P);
         if E=Ascendent then p := p.all.succ; else p := p.all.pred; end if;
      end loop;


   end Escriu;


   function esBuida(L: in LlistaParaules) return boolean is
      --retorna cert si la llista és buida.
   begin

      if L.Primer = null and L.Darrer = null then return true; end if;
      return false;
   end esBuida;

end d_llistaparaules;
