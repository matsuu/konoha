# クロージャへの道

大学の先生という職業柄、授業のついでに３年生にアンケートを取ってみたら、
最も憧れるプログラミング機能だったか、最も意味不明な機能だったか、
その辺りは忘れてしまったが、とりあえず第一位がクロージャ。

クロージャの認知度もだんだんと高まってきている感じがします。

そもそも、Konoha の言語設計は、Java 言語の文法をそのまま拝借するという方針で、
本家 Javaの方は、クロージャが追加される、追加されないとすったもんだのあげく、
どうやら Java7 では見送りになってしまったようです。そろそろ、コバンザメ作戦も
そろそろ破綻な兆しを感じています。

Konohaも、そろそろクロージャの実現に向けて、独自の準備を進めてみようという話に
なりました。

== そもそもクロージャって何なんだ？

って、話になります。
学生時代に習った話をそのまま書けば、レキシカルスコープでバインドされた実行時の環境を持った
無名関数のことです。（名前があってもいいのか知れませんが、）

これではよくわからないので、誰でも知っているC言語の関数ポインタから話を始めると、

{{{
typedef int (*incc_t)
int incc(int n)
{
   return n + 1;
}
}}}

typedef 

== どんな文法にする

Konoha は、トレーニングの負担を軽減するため、Java 言語の文法をそのまま拝借するという方針で、
本家 Java 言語の方は、

こうなると、影響が出てきます。やりたくはないけど、独自文法も覚悟しな
ければなりません。

さて、静的な型付き言語としては、クロージャといっても型が必要になります。

{{{
int(int) newfunc()　{
  int n = 1;
  return int(int x){ return x + n; }
}
}}}

う？　こんなクロージャは使い物になるのだろうか？ちょっと疑問です。

最近は、型推論でデキルだけ楽することを覚えてしまったので、
型推論で戻り値の型は推論することにして、もうちょっとシンプルにしてみました。

{{{
function newfunc() {
  int n = 1;
  return {int x => x + n }
}
}}}

== デリゲートから始める

まず、クロージャの実装を前に
C言語では、関数ポインタを使いまくっているので、関数ポインタを使わないCプログラミングなんて
ちょっと信じられません。

関数ポインタは、関数ポインタ
クロージャは、基本的にC言語の
クロージャなんて、半日もあれば追加できるさ、と息巻いて始めたのですが、
まずデリゲート(delegate)の追加からやりましょう。

Konoha に求められる機能を調べてみたら、第一位がクロージャ。

# aspect

void f(int n) {
  if(n < 0) throw new Security!!();
  proceed();
}

# generator 
 # iterative type
 # generator

int.. f(int n) {
  int i = 1, j = 1, next = 0;
  while(j < n) {
    next = i + j;
    yeild j;
    j = next; i = next;
  }
  return;
}

f(10)

void fnext(Ctx *ctx, knh_sfp_t *sfp)
{
  Iterator it sfp[]
  closure = it.getSource();
  v = c.callcc(c.cont)
  if(v != null) {
    c.contback()
  }
}

void fgen(Ctx *ctx, knh_sfp_t *sfp)
{
  c = new_Closure(ctx, sfp[0], sfp[-1]);
  c.call();
  
}


# closure

# Closure f = o # f;
f = {int x, y => x < y};

a = f(100,100)

class Closure {
  Object *base;
  Method *mtd;
  knh_sfp_t *stack;
  knh_sfp_t *ebp;
  size_t stack_size;
}

c.copystack()
c.invoke(100, 100)
c.backstack()

swap stack
push mtd
push base
push args
call mtd
swap stack


for(i = 0; i < 10; i++) {
	for(j = 0; j < 10; j++) {
		print i,j;
	}
}

