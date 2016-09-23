clear all
clc

disp('==========   SimpleObject   ==========')

a = SimpleObject('AAA') ;
b = SimpleObject('BB') ;
c = SimpleObject('C') ;

res = a.add('key1',1) ;
res = a.add('key2',2) ;
res = a.add('key3',3) ;

a.SetMatrix(magic(3)) ;
a.GetMatrix('d')

b.SetMatrix({
  'aaaaa', 'bb'
  'zzz', 'kkkk'
}) ;
b.GetMatrix('s')

d = a.query('key2') ;
d

b.Name
b.Name = 'ZZZ' ;
b.Name

clear all
%SimpleObject.ClearAll()

disp('==========   Functions   ==========')

cd('private')

  mexlib('spit_mtx')
  mexlib('reshape')

  a.tf=true;
  a.int=int32(42);
  a.dbl=42.42;
  a.string = 'aaa';

  my = a;
  my.str = a;
  for i = 1:5
    my.vstr(i) = a;
  end

  mexlib('describe',my)

cd('..')
