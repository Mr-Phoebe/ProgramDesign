# -*- coding: utf-8 -*-

class ExtractPCFG :
    def __init__(self):
        self.production_rules={}
        self.input_file_path="CFGrules.txt"
        self.output_file_path="PCFGrules.txt"

    def find_rules(self):
        inputfile=open(self.input_file_path,"r")
        outputfile=open(self.output_file_path,"w")
        lhs_dict={} #dictionary to hold count of LHS
        rule_dict={}
        for line in inputfile :
            line=line.rstrip()
            if line in rule_dict.keys():
                rule_dict[line]=rule_dict[line]+1
            else :
                rule_dict[line]=1
            lhs=line.split("->")[0]
            if lhs in lhs_dict.keys():
                lhs_dict[lhs]=lhs_dict[lhs]+1
            else :
                lhs_dict[lhs]=1
        for rule in rule_dict.keys():
            count_rule=rule_dict[rule]
            lhs=rule.split("->")[0]
            count_lhs=lhs_dict[lhs]
            rule_probability=count_rule/float(count_lhs)
            if(rule=='.->.'):
                outputfile.write('.->dot')
            elif (rule==',->,'):
                outputfile.write(',->comma')
            else :
                outputfile.write(rule)
            outputfile.write("#")
            outputfile.write(str(rule_probability))
            outputfile.write("\n")
        outputfile.close()
def main():
    ex=ExtractPCFG()
    ex.find_rules()


if __name__=="__main__" : main()

