with ada.Integer_Text_IO, HashExtern, ada.Text_IO; use ada.Integer_Text_IO,ada.Text_IO;

procedure main is

   s: string := "hola";
   p: string:= "hsola";

   function hash (s: in string; b: in positive) return natural is
      n: constant natural := s'last;
      m: constant natural:=character'pos(character'last)+1;
      c: natural;
      k,l: integer;
      a: array(1..n) of natural;
      r: array(1..2*n) of natural;
   begin
      for i in s'range loop a(i):=character'pos(s(i)); end loop;
      for i in 1..2*n loop r(i):=0; end loop;
      k:=2*n+1;
      for i in reverse 1..n loop
         k:=k-1; l:= k; c:= 0;
         for j in reverse 1..n loop
            c:=c+r(l) + a(i)*a(j);
            r(l) := c mod m; c:= c/m;
            l :=l-1;
         end loop;
         r(l) := c;
      end loop;
      c:=(r(n)*m + r(n+1)) mod b;
      return c;
   end hash;

   package MyHash is new HashExtern ( key => String,
                                      item => String,
                                     "=" => "=",
                                     Hash => hash);

begin

   if s=p then put("a"); end if;


end main;
