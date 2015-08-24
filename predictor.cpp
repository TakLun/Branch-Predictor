
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <sstream>
#include <bitset>
#include <math.h>
#include <unordered_map>

using namespace std;

void always_taken(ifstream*, ofstream*);
void always_non_taken(ifstream*, ofstream*);
void bimodal_single_bit(ifstream*, ofstream*, int);
void bimodal_two_bit(ifstream*, ofstream*, int);
void gshare(ifstream*, ofstream*, int);
void tournament(ifstream*, ofstream*);

typedef struct{

	string branch_address;
	int branch_result;

}Predictor;


int main(int argc, char *argv[]){

	ofstream outputfile;
	ifstream inputfile;
	
	if(argc != 3){
		printf("Error: Incorrect number of inputs\n");
		exit(0);
	}
		
	inputfile.open(argv[1]);
	if(!inputfile.is_open()){
		perror("Error\nUnable to open input file");
		exit(0);	
	}
	
	outputfile.open(argv[2]);
	if(!outputfile.is_open()){
		perror("Error\nUnable to open output file");
		exit(0);	
	}
	
	//Start Prediction
	
	always_taken(&inputfile, &outputfile);	
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	
	always_non_taken(&inputfile, &outputfile);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	

	bimodal_single_bit(&inputfile, &outputfile, 3);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 4);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 5);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 7);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 8);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 9);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_single_bit(&inputfile, &outputfile, 10);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	
	outputfile << endl;
	
	
	bimodal_two_bit(&inputfile, &outputfile, 3);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);

	bimodal_two_bit(&inputfile, &outputfile, 4);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_two_bit(&inputfile, &outputfile, 5);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_two_bit(&inputfile, &outputfile, 7);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_two_bit(&inputfile, &outputfile, 8);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_two_bit(&inputfile, &outputfile, 9);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	bimodal_two_bit(&inputfile, &outputfile, 10);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	
	outputfile << endl;
	
	
	gshare(&inputfile, &outputfile, 2);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 3);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 4);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 5);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 6);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 7);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 8);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 9);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);
	
	gshare(&inputfile, &outputfile, 10);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);

	outputfile << endl;
	
	tournament(&inputfile, &outputfile);
	inputfile.clear();
	inputfile.seekg(0, std::ios_base::beg);	

	inputfile.close();
	outputfile.close();
	return 0;
}

string translate_bits(string address, int index){
	
	int branch;
	string bitString;
	char low_bit[index];
	
	stringstream ss;
	
	string bit_index;
	
	ss << hex << address;
	ss >> branch;
	
	bitset<32> bits(branch);	
	
	bitString = bits.to_string<char,char_traits<char>,allocator<char> >();
	
	size_t length = bitString.copy(low_bit, index, bitString.length()-index);
	low_bit[length] = '\0';
	
	bit_index = low_bit;
	
	return bit_index;


}

Predictor parseString(string line){

	Predictor outcome;

	char branch[18];
	int result = 0;
	char trace[line.length()-18];
	line.copy(branch, 18,0);
	size_t length = line.copy(trace, line.length()-19,19);
	trace[length] = '\0';
	
	if(trace[0] == 'T'){
		result = 1;
	}else{
		result = 0;
	}
	
	outcome.branch_result = result;	
	outcome.branch_address = branch;
	
	return outcome;

}

void always_taken(ifstream *infile, ofstream *outfile){

	Predictor outcome;

	int branches = 0;
	int correct = 0;
	int result = 0;
	
	string line;
	
	while(!infile->eof()){
		
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome = parseString(line);
		
		if(outcome.branch_result == 1){
			correct++;
		}
		branches++;
	}
	
	result = ((float)correct/(float)branches)*100+.5;
	*outfile << result << endl;


}

void always_non_taken(ifstream *infile, ofstream *outfile){

	Predictor outcome;
	
	int branches = 0;
	int correct = 0;
	int result = 0;
	
	string line;
	
	while(!infile->eof()){
		
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome =  parseString(line);
		
		if(outcome.branch_result == 0){
			correct++;
		}
		branches++;
	}
	
	result = ((float)correct/(float)branches)*100+.5;
	*outfile << result << endl;


}

void bimodal_single_bit(ifstream *infile, ofstream *outfile, int table_size){

	Predictor outcome;
	
	unordered_map<string,int> addressmap;

	int correct = 0;
	int result = 0;
	int branches = 0;
	string line;
	
	string low_bit_string;
	char *low_bit_address;
	
	
	int entries = 0;
	
	
	while(!infile->eof()){
	
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome = parseString(line);
		
		
		low_bit_string = translate_bits(outcome.branch_address, table_size).c_str();
		low_bit_address = (char*)low_bit_string.c_str();

		unordered_map<string,int>::const_iterator it = addressmap.find(low_bit_address);
		
		if ( it == addressmap.end() ){
		
   			addressmap.insert({low_bit_address, 1});
   			
   			it = addressmap.find(low_bit_address);
   			
   			entries++;
		}
		
		if(it->second == outcome.branch_result)
			correct++;			
		else
			addressmap[it->first] = outcome.branch_result;
			
		
			
		branches++;
	
	}
	
	result = ((float)correct/(float)branches)*100+.5;
	*outfile << result << " ";

}




void bimodal_two_bit(ifstream *infile, ofstream *outfile, int table_size){
	
	Predictor outcome;
	
	unordered_map<string,int> addressmap;

	int correct = 0;
	int result = 0;
	int branches = 0;
	string line;
	
	string low_bit_string;
	char *low_bit_address;
	
	
	int entries = 0;
	
	int strongly_taken = 3;
	int weakly_taken = 2;
	int weakly_not_taken = 1;
	int strongly_not_taken = 0;
	
	
	while(!infile->eof()){
	
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome = parseString(line);
		
		
		low_bit_string = translate_bits(outcome.branch_address, table_size).c_str();
		low_bit_address = (char*)low_bit_string.c_str();

		unordered_map<string,int>::const_iterator it = addressmap.find(low_bit_address);
		
		if ( it == addressmap.end() ){
   			
   			addressmap.insert({low_bit_address, strongly_taken});
   			
   			it = addressmap.find(low_bit_address);
   			
   			entries++;
   			
		}
		
		if(outcome.branch_result == 1){
		
		
			if(it->second == strongly_taken || it->second == weakly_taken)
				correct++;				
						
						
			if(it->second < strongly_taken)
				addressmap[it->first] = addressmap[it->first] + 1;
			
		}else{
		
			if(it->second == strongly_not_taken || it->second == weakly_not_taken)
				correct++;
		
			if(it->second > strongly_not_taken)
				addressmap[it->first] = addressmap[it->first] - 1;
		
		}
		
			
		branches++;
	
	}
	
	result = ((float)correct/(float)branches)*100+.5;
	*outfile << result << " ";



}


void gshare(ifstream *infile, ofstream *outfile, int history){

	Predictor outcome;
	
	unordered_map<int,int> addressmap;

	int correct = 0;
	int result = 0;
	int branches = 0;
	string line;
	
	int table_size = 10;

	string low_bit_string;
	char *low_bit_address;	
	int translate_bit_address = 0;
	
	int strongly_taken = 3;
	int weakly_taken = 2;
	int weakly_not_taken = 1;
	int strongly_not_taken = 0;	
	
	int gshare_index = 0;
	int global_history = 0;
	
	int entries = 0;
		
	while(!infile->eof()){
	
		
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome = parseString(line);
		
		low_bit_string = translate_bits(outcome.branch_address, table_size).c_str();
		low_bit_address = (char*)low_bit_string.c_str();
		
		
		int exp = 0;
		for(int i=low_bit_string.length()-1;i>=0;i--){
			int temp = low_bit_address[i] - '0';
			
			if(temp == 1)
				translate_bit_address = translate_bit_address + pow(2, exp);
			
			exp++;
		}
		
		gshare_index = global_history ^ translate_bit_address;

		unordered_map<int,int>::const_iterator it = addressmap.find(gshare_index);
		
		if ( it == addressmap.end() ){
   			
   			addressmap.insert({gshare_index, strongly_taken});
   			
   			it = addressmap.find(gshare_index);
   			
   			entries++;
   			
		}
		
		if(outcome.branch_result == 1){
		
			if(it->second == strongly_taken || it->second == weakly_taken)
				correct++;
						
						
			if(it->second < strongly_taken)
				addressmap[it->first] = addressmap[it->first] + 1;
			
			global_history = (global_history << 1)+1;
			
		}else{
		
			if(it->second == strongly_not_taken || it->second == weakly_not_taken)
				correct++;
		
			if(it->second > strongly_not_taken)
				addressmap[it->first] = addressmap[it->first] - 1;
		
			global_history = global_history << 1;
		}
		
		
		translate_bit_address = 0;
		exp = 0;
					
		if(global_history >= pow(2, history))		
			global_history =  global_history - pow(2, history);
	
		branches++;
	}
	
	result = (((float)correct/(float)branches)*100)+.5;

	*outfile << result << " ";

}

void tournament(ifstream *infile, ofstream *outfile){

	Predictor outcome;
	
	unordered_map<int,int> gshare_map;
	unordered_map<string,int> bimodal_map;
	unordered_map<int,int> tourny_map;

	int correct = 0;
	int result = 0;
	int branches = 0;
	string line;
	
	int table_size = 10;
	int history = 10;

	string low_bit_string;
	char *low_bit_address;	
	int translate_bit_address = 0;
	
	int strongly_taken = 3;
	int weakly_taken = 2;
	int weakly_not_taken = 1;
	int strongly_not_taken = 0;	
	
	int gshare_index = 0;
	int global_history = 0;
	
	int address_number;
	int tourny_index = 0;

	stringstream ss;
	int tournament_prediction = 3;
	int prediction;
	
	
	int entries1 = 0;
	int entries2 = 0;
	int entries3 = 0;
	
	while(!infile->eof()){
	
		
		getline(*infile, line);
		if(line.empty())
			break;
			
		outcome = parseString(line);
		
		low_bit_string = translate_bits(outcome.branch_address, table_size).c_str();
		low_bit_address = (char*)low_bit_string.c_str();
		
		unordered_map<string,int>::const_iterator bit = bimodal_map.find(low_bit_address);
		
		if ( bit == bimodal_map.end() ){
   			
   			bimodal_map.insert({low_bit_address, strongly_taken});
   			
   			bit = bimodal_map.find(low_bit_address);
   			
   			entries2++;
   			
		}
		
		
		int exp = 0;
		for(int i=low_bit_string.length()-1;i>=0;i--){
			int temp = low_bit_address[i] - '0';
			
			if(temp == 1)
				translate_bit_address = translate_bit_address + pow(2, exp);
			
			exp++;
		}
		
		gshare_index = global_history ^ translate_bit_address;

		unordered_map<int,int>::const_iterator git = gshare_map.find(gshare_index);
		
		if ( git == gshare_map.end() ){
   			
   			gshare_map.insert({gshare_index, strongly_taken});
   			
   			git = gshare_map.find(gshare_index);
   			
   			entries1++;
   			
		}
		

		ss << low_bit_address;
		ss >> address_number;
		
		tourny_index = gshare_index^address_number;
		unordered_map<int,int>::const_iterator trn_it = tourny_map.find(tourny_index);
				
		if ( trn_it == tourny_map.end() ){
   			
   			tourny_map.insert({tourny_index, tournament_prediction});
   			
   			trn_it = tourny_map.find(tourny_index);
   			
   			entries3++;
   			
		}
		
				
		if(trn_it->second > 1){
			prediction = git->second;
		}else{
			prediction = bit->second;
		}
		
		if(outcome.branch_result == 1){
		
		
			if(prediction == strongly_taken || prediction == weakly_taken)
				correct++;
						
			if(bit->second == git->second){ 
	
			
			}else if((git->second == strongly_taken || git->second == strongly_taken) && (bit->second != strongly_taken || bit->second != strongly_taken)){
				
				if(trn_it->second < 3)			
					tourny_map[trn_it->first]++;
			}else{
			
				if(trn_it->second > 0)			
					tourny_map[trn_it->first]--;
			}
			
			if(git->second < strongly_taken)
				gshare_map[git->first] = gshare_map[git->first] + 1;
			
			if(bit->second < strongly_taken)
				bimodal_map[bit->first] = bimodal_map[bit->first] + 1;
			
			global_history = (global_history << 1)+1;
			
		}else{
		
			if(prediction == strongly_not_taken || prediction == weakly_not_taken)
				correct++;
		
			if(bit->second == git->second){
			
			}else if((git->second == strongly_not_taken || git->second == strongly_not_taken) && (bit->second != strongly_not_taken || bit->second != strongly_not_taken)){
			
				if(trn_it->second < 3)			
					tourny_map[trn_it->first]++;
			}else{
			
				if(trn_it->second > 0)			
					tourny_map[trn_it->first]--;
			}
			
			
			
			if(git->second > strongly_not_taken)
				gshare_map[git->first] = gshare_map[git->first] - 1;
			
			if(bit->second > strongly_not_taken)			
				bimodal_map[bit->first] = bimodal_map[bit->first] - 1;
		
			global_history = global_history << 1;
		}
		
		
		translate_bit_address = 0;
		exp = 0;
		
		if(global_history >= pow(2, history))		
			global_history =  global_history - pow(2, history);
		
		branches++;
		
	}

	result = ((float)correct/(float)branches)*100+.5;

	*outfile << result << " ";
}

