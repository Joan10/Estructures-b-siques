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

      subtype c_index is character range character'val(96)..'z';
      --subtipus emprat per indexar el vector.
      --Empram aquest i no el caràcter per si ens embullam amb els indexos que el compilador ens avisi.

      type d_Cistella is array (c_index) of LlistaParaules; --Declaram el tipus cistella, que és un vector indexat per caracters.

	Cistella: d_Cistella;
	l_max:integer;

      --funció que retorna la longitud màxima de les paraules d'una llista.
      function max_longitud(L: in LlistaParaules) return integer is
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
      L_act: LlistaParaules; --Lista de paraules per senyalar quina cistella estem processant.

      procedure treu_de_cistella is
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
         elsif nP.pred = null then
            L_act.Primer := nP.succ;
            L_act.Primer.pred := null;

         --El node és el darrer, per tant ajustam els punters.
         elsif nP.succ = null then
            L_act.Darrer := nP.pred;
            L_act.Darrer.succ := null;
         else
        --El node està enmig.
            nP.pred := nP.succ;
         end if;

      end treu_de_cistella;

   begin
     np:=L.Primer;
     l_max := max_longitud(L); --longitud màxima.

     while (nP/=null) loop
         c:=d_paraula.charPos(nP.P,l_max);
         Posa(Cistella(c), nP.P);
         nP:=nP.succ;
         --Put(c); Escriu(Cistella(c),Ascendent);
         new_line;
     end loop;
               for i in c_index loop --i és caracter que indexarà el vector.
         	L_act := Cistella(i);
         if not(esBuida(L_Act)) then Escriu(L_Act,Ascendent); end if;
         put('|');
      end loop;
     for n in reverse 1..l_max-1 loop
         --Assignam a la cistella que processam la cistella del valor anterior a 'a'.
         for i in c_index loop --i és caracter que indexarà el vector.
            L_act := Cistella(i); nP:=L_act.Primer;
            while (np /= null) loop
               c:=d_paraula.charPos(nP.P,n);
               if (c /= i) then
                  posa(Cistella(c),nP.P);
                  new_line;new_line;

         for i in c_index loop --i és caracter que indexarà el vector.
         	L_act := Cistella(i);
                     if not(esBuida(L_Act)) then Escriu(L_Act,Ascendent); end if;
                     put('|');
                  end loop;

                  treu_de_cistella; new_line;
                  new_line;new_line;
               end if;

               nP:=nP.succ;
            end loop;
      	end loop;
     end loop;



   end Ordena;

   procedure Escriu(L: in LlistaParaules; E: e_Ordre) is
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
   begin

      if L.Primer = null and L.Darrer = null then return true; end if;
      return false;
   end esBuida;

end d_llistaparaules;
