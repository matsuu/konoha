using time.*;
Time t = new Time();
print "time;";
print "year :"+t.getYear();
print "month:"+t.getMonth();
print "day  :"+t.getDay();
print "hour :"+t.getHour();
print "min  :"+t.getMinute();
print "sec  :"+t.getSecond();

print "";

t.setTime(1988,3,14,13,45,34);
print "set time;";
print "year :"+t.getYear();
print "month:"+t.getMonth();
print "day  :"+t.getDay();
print "hour :"+t.getHour();
print "min  :"+t.getMinute();
print "sec  :"+t.getSecond();
