# -*- coding: utf-8 -*-

class PCFGtoCNF :
    def __init__(self):
        self.production_rules={}
        self.input_file_path="PCFGrules.txt"
        self.output_file_path="CNFrules.txt"
        self.non_terminal_file_path="non_terminals.txt"

    def find_rules(self):
        inputfile=open(self.input_file_path,"r")
        outputfile=open(self.output_file_path,"w")
        lhs_dict={}         #dictionary to hold count of LHS
        rule_dict={}
        nt_file=open(self.non_terminal_file_path,"r")
        V=[]                #list of non terminals
        final_rules=[]
        intermediate_rules={}
        change_rules={}
        rules=[]
        for line in nt_file:
            V=line.split()
        #STEP 1 : keep only terminal rules & replace single value rhs non-terminals
        for line in inputfile :
            rule=line.rstrip()
            split_txt=line.split("->")
            lhs=split_txt[0]
            rhs=split_txt[1].split("#")[0]
            rhs_tokens=rhs.split()
            if len(rhs_tokens)==1:            #check if terminal rule add the rule to CNF
                if(rhs_tokens[0] not in V) :  #the only element
                    final_rules.append(rule)
                    intermediate_rules[rule]=lhs
                else :
                    change_rules[rule]=lhs

            else :
                 intermediate_rules[rule]=lhs
        new_intermediate_rules={}
        for rule in change_rules :
            line=rule
            rule_txt=rule.split("->")
            lhs=rule_txt[0]
            rhs_txt=rule_txt[1].split("#")
            rhs=rhs_txt[0]
            prob=float(rhs_txt[1])

            all_rhs=[]

            if rhs in change_rules.values(): #if RHS is in the set of single non terminal rules

                rhs_chain=rhs
                new_prob=prob
                list_of_chain=[]

                for rule_read in change_rules:
                    if(rhs_chain==change_rules[rule_read]):
                        #rule_read=
                        list_of_chain.append(rule_read.split("#")[0].split("->")[1])

                for rhs_chain1 in list_of_chain :
                        while rhs_chain1 in change_rules.values() :
                            for rhs_rule in change_rules :
                                    if(rhs_chain1==change_rules[rhs_rule]):
                                        rhs_chain1=rhs_rule.split("->")[1].split("#")[0]
                        all_rhs.append(rhs_chain1)
            if rhs in intermediate_rules.values():
                all_rhs.append(rhs)


            for rhs_token in all_rhs:
                if rhs_token in intermediate_rules.values():
                    for int_rule in intermediate_rules :
                        if(rhs_token==intermediate_rules[int_rule]):
                            int_rule_txt=int_rule.split("->")[1]
                            int_rule_rhs_tokens=int_rule_txt.split("#")
                            probability=float(int_rule_rhs_tokens[1])
                            int_rule_rhs=int_rule_rhs_tokens[0]
                            new_prob=prob*probability
                            new_rule=lhs+"->"+int_rule_rhs+"#"+str(new_prob)
                            new_intermediate_rules[new_rule]=lhs
                            final_rules.append(new_rule)


        for key in new_intermediate_rules.keys():
            intermediate_rules[key]=new_intermediate_rules[key]


        #STEP 2 : keep only terminal rules & replace single value rhs non-terminals
        for key in intermediate_rules.keys():
            rule_prob_txt=key.split("#")
            rule=rule_prob_txt[0]
            prob=rule_prob_txt[1]
            rule_txt=rule.split("->")
            lhs=rule_txt[0]
            rhs=rule_txt[1]
            rhs_tokens=rhs.split()
            if(len(rhs_tokens))==2:
                final_rules.append(key)
            elif(len(rhs_tokens))>2:
                joinees=rhs_tokens[:-1]
                no_of_joinees=len(rhs_tokens)-1
                joint="-".join(joinees)
                rule1=lhs+"->"+joint+" "+rhs_tokens[len(rhs_tokens)-1]+"#"+prob
                if not rule1 in final_rules:
                    final_rules.append(rule1)
                while (no_of_joinees >=2):
                    lhs=joint
                    rhs_joinee_tokens=joint.split("-")
                    new_joinees=rhs_joinee_tokens[:-1]
                    new_joint="-".join(new_joinees)
                    last_token=rhs_joinee_tokens[no_of_joinees-1]
                    joinee_rule=lhs+"->"+new_joint+" "+last_token+"#1"
                    no_of_joinees=no_of_joinees-1
                    joint=new_joint
                    if not joinee_rule in final_rules:
                        final_rules.append(joinee_rule)

        for rule in final_rules:
            outputfile.write(rule)
            outputfile.write("\n")
        outputfile.close()

def main():
    ex=PCFGtoCNF()
    ex.find_rules()


if __name__=="__main__" : main()

