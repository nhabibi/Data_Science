import java.util.Random;
import java.util.Vector;
import java.io.*;

public class GA {

	static final int hypothesisLength = 10;
	static float fitness_threshold, r, m;
	static int p;
	static String examplesFile;
	static String[] population;
	static int[] fitnesses;
	Vector examples = new Vector();
	int[] probabilitiesContainer;
		
	
	public static void main(String[] args) {
		
		//args: fitness_threshold + p + r + m + exampleFiles
		fitness_threshold = Float.parseFloat(args[0]); //Temporarily
		p = Integer.parseInt(args[1]);
		r = Float.parseFloat(args[2]);
		m = Float.parseFloat(args[3]);
		examplesFile = args[4];
		
		population = new String[p];
		fitnesses = new int[p];
		
		new GA().start();
	}	
//*********************************************************************
		void start(){
			
			readExamples();
			fitness_threshold  = fitness_threshold * examples.size();
			initializePopulation();
			int max = 0;
			int iteration = 1;
			while( (max = findMaxFitnessOfPopulation()) < fitness_threshold ){

				//just for display
				iteration++;
				System.out.println("\n\n***Next Iteration***\n");
				for(int i=0; i<p; ++i){
					System.out.println("Fitness of " + population[i] + ": " + fitnesses[i]);
				}
				System.out.println("\nMax of Fitnesses: " + max);
				//generate next population				
				population = createNewPopulation();
			}//while
			
			System.out.println("\n\n***Last Iteration***\n");
			for(int i=0; i<p; ++i){
				System.out.println("Fitness of " + population[i] + ": " + fitnesses[i]);
			}
			System.out.println("\nMax of Fitnesses: " + max);
            System.out.println("\nNumber of Iterations: " + iteration);
		}
//*********************************************************************
		void readExamples(){
			
			//System.out.println("***Examples***");
			try{
				BufferedReader br = new BufferedReader(new FileReader(examplesFile));
				String line = br.readLine();
				while (line != null){
					String nextExample = parseExample(line);
					if (!nextExample.equals(""))
						examples.addElement(nextExample);
					line = br.readLine();
				}
			}
			catch(Exception e){
				System.out.println("In readExamples: " + e.getMessage());
			}
		}
//*********************************************************************
/* 1-outlook = sunny|overcast|rain
 * 2-tempreture = hot|mild|cool
 * 3-humidity = high|normal
 * 4-wind = weak|strong
 * 5-playTennis = Yes|No
 */	
/*note: substring(int): from int till end
		substring(int1,int2) : from int1 till int2-1
*/		
		String parseExample(String line){
			
			if (line.equals(""))  return ""; //for cuation,if sent line=""
			String result = "";
		    String nextAttr = "";
			int kama;
			line = line.toLowerCase();
			
			//1-outlook
			kama = line.indexOf(",");
			nextAttr = line.substring(0,kama);
			line = line.substring(kama+1);
			if (!nextAttr.equals(""))
				if( nextAttr.equals("sunny"))
					result += "100";
			    else if ( nextAttr.equals("overcast"))
				    result += "010";
				else if ( nextAttr.equals("rain"))
					result += "001";
				else //set to defualt value
					result += "100";
			else //attribute not defined
				result += "111";
			//2-tempreture
			kama = line.indexOf(",");
			nextAttr = line.substring(0,kama);
			line = line.substring(kama+1);
			if (!nextAttr.equals(""))
				if( nextAttr.equals("hot"))
					result += "100";
			    else if ( nextAttr.equals("mild"))
				    result += "010";
				else if ( nextAttr.equals("cool"))
					result += "001";
				else //set to defualt value
					result += "100";
			else //attribute not defined
				result += "111";
			//3-humidity
			kama = line.indexOf(",");
			nextAttr = line.substring(0,kama);
			line = line.substring(kama+1);
			if (!nextAttr.equals(""))
				if( nextAttr.equals("high"))
					result += "10";
			    else if ( nextAttr.equals("normal"))
				    result += "01";
				else //set to defualt value
					result += "100";
			else //attribute not defined
				result += "11";
			//4-wind
			kama = line.indexOf(",");
			nextAttr = line.substring(0,kama);
			line = line.substring(kama+1);
			if (!nextAttr.equals(""))
				if( nextAttr.equals("weak"))
					result += "10";
			    else if ( nextAttr.equals("strong"))
				    result += "01";
				else //set to defualt value
					result += "100";
			else //attribute not defined
				result += "11";
			//5-playTennis
			nextAttr = line;
			if (!nextAttr.equals(""))
				if( nextAttr.equals("yes"))
					result += "10";
			    else if ( nextAttr.equals("no"))
				    result += "01";
				else //set to defualt value
					result += "10";
			else //we sholud ignore this example
				result = "";
			//System.out.println(result);
			return result;	
		}
//*********************************************************************		
//*********************************************************************
		void initializePopulation(){
			
			//System.out.println("***Population***");
			
			Random rand = new Random();
			for(int i=0; i<p; ++i){
				
				String hypothesis = "";
				//number = rand.nextInt(1023);
				for(int j=0; j<hypothesisLength; ++j){
					//ToDO: with binary operator
					if (rand.nextBoolean())  hypothesis += "1";
					else  hypothesis += "0";
				}
				if (isValid(hypothesis)){
					population[i] = (hypothesis);
				    //System.out.println(hypothesis);
			    }
				else  --i; //the entry for i is remained empty,so again
			}		
		}
//*********************************************************************
		boolean isValid(String hypo){
			
			String outlook = hypo.substring(0,3);
			String tempreture = hypo.substring(3,6);
			String humidity = hypo.substring(6,8);
			String wind = hypo.substring(8,10);
			if (!outlook.equals("000") &&
			    !tempreture.equals("000") &&
			    !humidity.equals("00") &&
			    !wind.equals("00"))
				return true;
			return false;				
		}
//*********************************************************************		
		int findMaxFitnessOfPopulation(){
			
			assignFitnessToPopulation();
			int max = 0;
			for (int i=0; i<p; ++i){
				if(fitnesses[i]> max)   max = fitnesses[i];
			}
			return max;
		}
//*********************************************************************
/*we put only hypothesis with targetValue==Yes in polulation;
 * so:1-if precondition of an example is consistent with hypo
 * and its targetValue==Yes ==> increment the correctness for hypo
 * 2-if precondition of an example is not consistent with hypo
 * and its targetValue==No ==> increment the correctness for hypo
 */
		
		void assignFitnessToPopulation(){
			
			//System.out.println("\n***Fitnesses***");
			
			int correctness;
			for(int i=0; i<p; ++i){
				correctness = 0;
				for(int j =0; j<examples.size(); ++j){
					String example = (String)examples.elementAt(j);
					String precondition = example.substring(0,10);
					String postcondition = example.substring(10,12);
					if (isCompatible(precondition, population[i]) ){
						if (postcondition.equals("10"))
							++correctness;
					}
					else {
						if (postcondition.equals("01"))
							++correctness;
					}
				}
				fitnesses[i] = correctness;
				//System.out.println("fitness of " + i + " " + fitnesses[i]);
			}
		}
//*********************************************************************
		boolean isCompatible(String pre, String pop){
			
			for(int i=0; i<pre.length(); ++i)
				if (pre.charAt(i)== '1' && pop.charAt(i)!= '1')
					return false;
			return true;
		}
//*********************************************************************		
		String[] createNewPopulation(){
			
			String[] ps = new String[p];
			//first fill probabilities Container :D
			int sum =0;
			int index = 0;
			for(int i=0; i<p; ++i)
				sum += fitnesses[i];
			probabilitiesContainer = new int[sum];
			for(int i=0; i<p; ++i){ //for all hypos
				for(int j =0; j<fitnesses[i]; ++j){
					probabilitiesContainer[index] = i;
					//System.out.println(probabilitiesContainer[index]);
					++index;
				}
			}
			int selectNum,crossoverNum;
			int temp = Math.round(r * p);
			if (temp % 2 == 0){//if it is even
				selectNum = p - temp;
				crossoverNum = temp;
			}
			else{//if it is odd
				selectNum = p - temp - 1;
				crossoverNum = temp + 1;
			}
			//System.out.println("selectNum: " + selectNum);
			//System.out.println("crossoverNum: " + crossoverNum);
			
			select(ps, selectNum);
			crossover(ps, crossoverNum, selectNum);
			mutate(ps);
			return ps;
		}
//*********************************************************************
		void select(String[] ps,int number){
			
			Random rand = new Random();
			int[] temp = probabilitiesContainer;
			
			for(int i=0; i< number; ++i){
				
				ps[i] = selectOneHypo(temp, rand);
		    }
		}
//*********************************************************************
//this method does a single-point crossover		
		void crossover(String[] ps, int number, int startFrom){
			
			Random rand1 = new Random();//for hypo
			Random rand2 = new Random();//for point
			String hypo11 ="";String hypo12 ="";String hypo21 ="";String hypo22 ="";
			int[] temp = probabilitiesContainer;
			
			for(int i=0; i< number/2; ++i){
				//frist select 2 hypo prob.
				String hypo1 = selectOneHypo(temp, rand1);
				String hypo2 = selectOneHypo(temp, rand1);
				//select a crossover point
				int point = rand2.nextInt(hypothesisLength);
				//now create 2 new hypos
				hypo11 = hypo1.substring(0, point);
				hypo12 = hypo1.substring(point);
				hypo21 = hypo2.substring(0, point);
				hypo22 = hypo2.substring(point);
				ps[startFrom++] = hypo11 + hypo22;
				ps[startFrom++] = hypo21 + hypo12;
				
				//System.out.println("hypo1 & hypo2 before cross: " + hypo1 + " " + hypo2);
				//System.out.println("point: " + point);
				//System.out.println("hypo1 & hypo2 after cross: " + hypo11 + hypo22 + " " + hypo21 + hypo12);
			}
		}
//*********************************************************************
		String selectOneHypo(int[] temp, Random rand){
			
			while(true){
				
				int index = rand.nextInt(temp.length);
				int hypo = temp[index];
				if(hypo != -1){//if already has not been selected
					//remove it from selection
					for(int j=0; j<temp.length; ++j){
						if (temp[j] == hypo)
							temp[j] = -1;
					}
					//exit loop
					return population[hypo];
				}//if
		    }//while
		}			
//*********************************************************************
		void mutate(String[] ps){
			
			Random rand1 = new Random();
			Random rand2 = new Random();
			int number = Math.round(m * p);
			
			for(int i=0; i< number; ++i){
				//select a hypo prob.
				int index = rand1.nextInt(ps.length);
				String hypo = ps[index];
				//System.out.println("hypo before mutation: "+ hypo);
				//select a position prob.
				int position = rand2.nextInt(hypothesisLength);
				char bit = hypo.charAt(position);
				//now invert
				String hypo1 = hypo.substring(0, position);
				String hypo2 = hypo.substring(position+1);
				if (bit == '1')
					ps[index] = hypo1 + "0" + hypo2;
				else
					ps[index] = hypo1 + "1" + hypo2;
				//System.out.println("hypo after mutation: "+ ps[index]);
			}
			
		}
//*********************************************************************
}
