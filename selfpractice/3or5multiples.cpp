int solution(int number) {
 if (number <=0) return 0;
 int sum = 0;
 for (int counter= 0; counter < number; counter++){
     if (counter%3 == 0) {
         sum += counter;
     }
     else{
         if (counter%5 == 0) {
             sum += counter;
         }
     }
 }   
 return sum;
}
