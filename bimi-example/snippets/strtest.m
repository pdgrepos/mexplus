clear
clc

disp('==========   Numbers   ==========')
s = 42 ;
v = [ 42 42 42 42 42 42 ] ;
m = reshape(v,2,3) ;

res = [] ;
res = [ res ; [ isscalar(s) isscalar(v)  isscalar(m) ] ] ;
res = [ res ; [ isvector(s) isvector(v)  isvector(m) ] ] ;
res = [ res ; [ ismatrix(s) ismatrix(v)  ismatrix(m) ] ] ;

res

disp('==========   Strings   ==========')
s_a = 'gino' ;
s_b = s_a' ;
cs_a = { 'hello' , 'yes' , 'no' , 'goodbye' } ;
cs_b = { 'hello' , 'yes' ; 'no' , 'goodbye' } ;
cs_c = { 'hello' ; 'yes' ; 'no' ; 'goodbye' } ;
vs = [ 'aaaa' ; 'bbbb' ; 'cccc' ; 'dddd' ] ;

res = [] ;
res = [ res ;   ischar(s_a)    ischar(s_b)    ischar(cs_a) ischar(cs_b) ischar(cs_c) ischar(vs) ] ;
res = [ res ; [ isscalar(s_a)  isscalar(s_b)  isscalar(cs_a) isscalar(cs_b) isscalar(cs_c) isscalar(vs) ] ] ;
res = [ res ; [ isvector(s_a)  isvector(s_b)  isvector(cs_a) isvector(cs_b) isvector(cs_c) isvector(vs) ] ] ;
res = [ res ; [ ismatrix(s_a)  ismatrix(s_b)  ismatrix(cs_a) ismatrix(cs_b) ismatrix(cs_c) ismatrix(vs) ] ] ;
res = [ res ; [ iscellstr(s_a) iscellstr(s_b) iscellstr(cs_a) iscellstr(cs_b) iscellstr(cs_c) iscellstr(vs) ] ] ;

res

