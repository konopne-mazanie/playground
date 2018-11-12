unit drawenv;

{$mode objfpc}{$H+}

interface

uses
   crt;

procedure drawenv_draw();
procedure drawenv_pl(x,oldy,y:integer);
procedure drawenv_ball(oldx,oldy,x,y:integer);
implementation
procedure drawenv_draw();
var i:integer;
begin
TextBackground(Blue);
 for i:=1 to 60 do write(' ');
 gotoxy(1,20);
 for i:=1 to 60 do write(' ');
 for i:=2 to 19 do begin
   gotoxy(1,i);
   write(' ');
   gotoxy(60,i);
   write(' ');
 end;

 TextBackground(Black);
 gotoxy(1,21);
 write('Tvoje skore: ');
 gotoxy(25,21);
 write('Sipka Hore/Dole: pohyb    ESC: ukonc');
 gotoxy(1,22);
 write('Level: ');
 gotoxy(39,22);
 write('Vytvoril Peter Uhrecky');
end;

procedure drawenv_pl(x,oldy,y:integer);
var i:integer;
begin
if oldy<>0 then begin
for i:=oldy to oldy+2 do begin
 gotoxy(x,i);
 write(' ');
end;

end;
TextBackground(Green);
for i:=y to y+2 do begin
 gotoxy(x,i);
 write(' ');
end;
TextBackground(Black);
end;

procedure drawenv_ball(oldx,oldy,x,y:integer);
begin
if oldx<>0 then begin
 gotoxy(oldx,oldy);
 write(' ');
end;
TextBackground(White);
gotoxy(x,y);
write(' ');
TextBackground(Black);
end;

end.

