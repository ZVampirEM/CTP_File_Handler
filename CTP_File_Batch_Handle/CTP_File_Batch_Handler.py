#-*- coding=utf-8 -*-

'''
Created on Mar 7, 2016

@author: Enming.Zhang

All files which this scripr can handler is must be encoding in utf-8
'''

import re

class batch_handler:
    CThostFtdc_list     = []
    m_ThostFtdc_list    = []
    Call_Back_Functions_list = []
    Req_Functions_list  = []
    FemasTHelper_h_content_list = []
    FemasTHelper_cpp_content_list = []
    FemasSpiMessage_h_content_list = []
    TraderFemasHandler_h_content_list = []
    
    Fields_Relation_dict = {}
    CThostFtdc_and_mThostFtdc_Relation_dict = {}
    Functions_Relation_dict = {}
    Call_Back_Function_and_param_dict = {}
    
    target_location_in_list = 0
    
    def extract_cthostftdc_fields_from_api_struct(self):
        
        ThostFtdcUserApiStruct_h_file = open("ThostFtdcUserApiStruct.h", 'r')
        ThostFtdcUserApiStruct_h_line = ThostFtdcUserApiStruct_h_file.readline()
        while ThostFtdcUserApiStruct_h_line:
            ThostFtdcUserApiStruct_h_match_object = re.findall("CThostFtdc\w+Field", ThostFtdcUserApiStruct_h_line)
            if ThostFtdcUserApiStruct_h_match_object != [] and re.findall("struct", ThostFtdcUserApiStruct_h_line) != []:
                self.CThostFtdc_list.extend(ThostFtdcUserApiStruct_h_match_object)
                '''
                the format should be:
                /// comment
                var declaration
                '''
                ThostFtdcUserApiStruct_h_line = ThostFtdcUserApiStruct_h_file.readline()
                struct_element_list = []
                while ThostFtdcUserApiStruct_h_line != "};\n" and ThostFtdcUserApiStruct_h_line != "};":
                    comment_match_object = re.findall(r"///([\x80-\xff','', '\w\d'/']+)", ThostFtdcUserApiStruct_h_line)
                    if comment_match_object != []:
                        every_line_list = []
                        
                        every_line_list.extend(comment_match_object)
                        
                        ThostFtdcUserApiStruct_h_line = ThostFtdcUserApiStruct_h_file.readline()
                        declaration_match_object = re.findall("[\\t' ']+(.*?)[\\t' ']+(.*?);", ThostFtdcUserApiStruct_h_line)
                        if declaration_match_object != []:
                            every_line_list.append(declaration_match_object[0][0])
                            every_line_list.append(declaration_match_object[0][1])
                            struct_element_list.append(every_line_list)
                    ThostFtdcUserApiStruct_h_line = ThostFtdcUserApiStruct_h_file.readline()
                
                if struct_element_list != []:
                    self.Fields_Relation_dict[ThostFtdcUserApiStruct_h_match_object[0]] = struct_element_list
                    
            ThostFtdcUserApiStruct_h_line = ThostFtdcUserApiStruct_h_file.readline()
            
        ThostFtdcUserApiStruct_h_file.close()
        
    
    def extract_callback_functions_and_reqfunctions_from_trade_api(self):
        ThostFtdcTraderApi_h_line_prev = ""
        ThostFtdcTraderApi_h_file = open("ThostFtdcTraderApi.h", 'r')
        ThostFtdcTraderApi_h_line = ThostFtdcTraderApi_h_file.readline()
        while ThostFtdcTraderApi_h_line:
            ThostFtdcTraderApi_h_match_object_on = re.findall("On['Rsp''Rtn''Err']\w+", ThostFtdcTraderApi_h_line)
            ThostFtdcTraderApi_h_match_object_req = re.findall(" (Req\w+)\(", ThostFtdcTraderApi_h_line)
            if ThostFtdcTraderApi_h_match_object_on != [] and re.findall("virtual", ThostFtdcTraderApi_h_line) != []:
                self.Call_Back_Functions_list.extend(ThostFtdcTraderApi_h_match_object_on)
                param_match_object = re.search("CThost[\w' '',''*']+", ThostFtdcTraderApi_h_line)
                param_list = re.split(", ", param_match_object.group())
                On_comment_match_object = re.findall(r"///([\x80-\xff','', '\w\d'/']+)", ThostFtdcTraderApi_h_line_prev)
                param_list.extend(On_comment_match_object)
                self.Call_Back_Function_and_param_dict[ThostFtdcTraderApi_h_match_object_on[0]] = param_list
                
            elif ThostFtdcTraderApi_h_match_object_req != [] and re.findall("virtual", ThostFtdcTraderApi_h_line) != []:
                self.Req_Functions_list.extend(ThostFtdcTraderApi_h_match_object_req)
                every_function_list = []
                '''
                the format should be:
                /// comment
                var declaration
                '''
                comment_match_object = re.findall(r"///([\x80-\xff','', '\w\d'/']+)", ThostFtdcTraderApi_h_line_prev)
                if comment_match_object != []:
                    every_function_list.extend(comment_match_object)
                else:
                    print "the function has no comment"
                    every_function_list.append(" ")
                param_match_object = re.findall("CThostFtdc\w+", ThostFtdcTraderApi_h_line)
                if param_match_object != []:
                    every_function_list.extend(param_match_object)
                
                self.Functions_Relation_dict[ThostFtdcTraderApi_h_match_object_req[0]] = every_function_list
            
            ThostFtdcTraderApi_h_line_prev = ThostFtdcTraderApi_h_line
            ThostFtdcTraderApi_h_line = ThostFtdcTraderApi_h_file.readline()
        
        ThostFtdcTraderApi_h_file.close()
    
    '''
    convert the content of assigned file into a list
    '''
        
    def transition_content_in_file_to_list(self, file_name, relation_list):
#        relation_list = []
        operated_file = open(file_name, 'r')
        file_line = operated_file.readline()
        while file_line:
            relation_list.append(file_line)
            file_line = operated_file.readline()
        operated_file.close()
        
    def clear_content_in_file(self, file_name):
        clear_file = open(file_name, 'w+')
        clear_file.seek(0)
        clear_file.write(' ')
        clear_file.close()
        
    '''
    update the FemasTHelper.cpp
    '''
    def update_file_with_content_list(self, file_name, relation_list):
        '''
        the file need to be clear for update at first
        '''
        self.clear_content_in_file(file_name)
        Input_Content = ''.join(relation_list)
        operated_file = open(file_name, 'r+')
        operated_file.seek(0)
        operated_file.write(Input_Content)
        operated_file.close()
    
    def update_FemasTHelper_h(self):
        self.FemasTHelper_h_content_list = []
        self.transition_content_in_file_to_list("FemasTHelper.h", self.FemasTHelper_h_content_list)
        self.target_location_in_list = 0
        for line in self.FemasTHelper_h_content_list:
            if re.search("CFemasTHelper", line) != None and re.search("class", line) != None:
                self.target_location_in_list += 1
                while self.FemasTHelper_h_content_list[self.target_location_in_list] != "};" and self.FemasTHelper_h_content_list[self.target_location_in_list] != "};\n":
                    if re.search("CThostFtdc\w+Field", self.FemasTHelper_h_content_list[self.target_location_in_list]) != None and \
                       re.search("m_ThostFtdc\w+", self.FemasTHelper_h_content_list[self.target_location_in_list]) != None:
                        self.FemasTHelper_h_content_list.pop(self.target_location_in_list)
                        continue
                    
                    elif re.search("On['Rsp''Rtn''Err']\w+\([' ''*'\w]+\);", self.FemasTHelper_h_content_list[self.target_location_in_list]) != None and \
                         re.search("void", self.FemasTHelper_h_content_list[self.target_location_in_list]) != None:
                        self.FemasTHelper_h_content_list.pop(self.target_location_in_list)
                        continue
                    
                    self.target_location_in_list += 1
                break
            self.target_location_in_list += 1
        for cthostftdc_ele in self.CThostFtdc_list:
            self.FemasTHelper_h_content_list.insert(self.target_location_in_list, " " * 4 + cthostftdc_ele + " " * (56 - 4 - len(cthostftdc_ele)) + cthostftdc_ele.replace('CThostFtdc', 'm_ThostFtdc') + ';\n')
            self.m_ThostFtdc_list.append(cthostftdc_ele.replace('CThostFtdc', 'm_ThostFtdc'))
            self.CThostFtdc_and_mThostFtdc_Relation_dict[cthostftdc_ele] = cthostftdc_ele.replace('CThostFtdc', 'm_ThostFtdc')
            self.target_location_in_list += 1
        
        for call_back_function in self.Call_Back_Functions_list:
            self.FemasTHelper_h_content_list.insert(self.target_location_in_list, " " * 4 + "void" + " " * 48 + call_back_function + "(CThostSpiMessage *pSpiMsg);\n")
            self.target_location_in_list += 1
            
        self.update_file_with_content_list("FemasTHelper.h", self.FemasTHelper_h_content_list)
    
    def update_FemasSpiMessage_h(self):
        self.FemasSpiMessage_h_content_list = []
        self.transition_content_in_file_to_list("FemasSpiMessage.h", self.FemasSpiMessage_h_content_list)
        self.target_location_in_list = 0
        for line in self.FemasSpiMessage_h_content_list:
            if re.search("enum MSG_TYPE", line) != None:
                self.target_location_in_list += 1
                need_deleted_index = self.target_location_in_list
                while self.FemasSpiMessage_h_content_list[need_deleted_index] != "\t\t};\n" and self.FemasSpiMessage_h_content_list[need_deleted_index] != "\t\t};":
                    self.FemasSpiMessage_h_content_list.pop(need_deleted_index)
                self.FemasSpiMessage_h_content_list.pop(need_deleted_index)
                self.FemasSpiMessage_h_content_list.insert(self.target_location_in_list, "\t" * 2 + "{\n")
                self.target_location_in_list += 1
                self.FemasSpiMessage_h_content_list.insert(self.target_location_in_list, "\t" * 3 + "//====================== API_MSG_TYPE ======================\n")
                for ele in self.Call_Back_Functions_list:
                    self.target_location_in_list += 1
                    self.FemasSpiMessage_h_content_list.insert(self.target_location_in_list, "\t" * 3 + ele + ",\n")
                self.target_location_in_list += 1
                self.FemasSpiMessage_h_content_list.insert(self.target_location_in_list, "\t" * 3 + "//====================== API_MSG_TYPE ======================\n")
                self.target_location_in_list += 1
                self.FemasSpiMessage_h_content_list.insert(self.target_location_in_list, "\t\t};\n")
                break
            self.target_location_in_list += 1
        self.update_file_with_content_list("FemasSpiMessage.h", self.FemasSpiMessage_h_content_list)
        
    def update_TraderFemasHandler_h(self):
        self.TraderFemasHandler_h_content_list = []
        self.transition_content_in_file_to_list("TraderFemasHandler.h", self.TraderFemasHandler_h_content_list)
        self.target_location_in_list = 0
        for line in self.TraderFemasHandler_h_content_list:
            match_object = re.search("virtual void (On[Rsp|Rtn|Err]\w+)", line)
            if match_object != None and match_object.group(1) in self.Call_Back_Functions_list and re.search(r'//', line) == None:
                '''
                the format must be:
                ///comment
                function declaration
                
                and all Rsp/Rtn/Err call back functions must write in continuous
                '''
                need_deleted_line = self.target_location_in_list - 1
                if need_deleted_line >= 0:
                    self.TraderFemasHandler_h_content_list = self.TraderFemasHandler_h_content_list[0 : need_deleted_line]
                for function in self.Call_Back_Functions_list:
                    self.TraderFemasHandler_h_content_list.append("///" + self.Call_Back_Function_and_param_dict[function][-1] + "\n")         
                    self.TraderFemasHandler_h_content_list.append("virtual void " + function + "(" + ", ".join(self.Call_Back_Function_and_param_dict[function][0 : -1]) + ") {\n")
                    write_list = []
                    for param in self.Call_Back_Function_and_param_dict[function][0 : -1]:
                        match_param = re.search("[' ''*']+(\w+)", param)
                        if match_param != None:
                            if re.search("CThostFtdcRspInfoField", param) != None:
                                write_list.append("(ThostFtdcRspInfoField*)" + match_param.group(1))
                            else:
                                write_list.append(match_param.group(1))
                    self.TraderFemasHandler_h_content_list.append("\tAddMsg(new CThostSpiMessage(SPI::" + function + ", " + ", ".join(write_list) + "));\n")
                    self.TraderFemasHandler_h_content_list.append("};\n\n")
                self.TraderFemasHandler_h_content_list.append("};\n")
                break
            self.target_location_in_list += 1
            
        self.update_file_with_content_list("TraderFemasHandler.h", self.TraderFemasHandler_h_content_list)
    
    '''
    update the InitMembers
    '''    
    def update_InitMembers(self):
        self.target_location_in_list = 0
        Modify_FemasTHelper_cpp_content_list = self.FemasTHelper_cpp_content_list
        for line in Modify_FemasTHelper_cpp_content_list:
            if (re.search("InitMembers", line) != None):
                self.target_location_in_list += 1
                '''
                clear the current content of InitMembers
                '''
                Need_Delete_line = self.target_location_in_list
                while Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}\n" and Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}":
                    Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                
                
                '''
                insert the updating content into InitMembers
                '''
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "{\n")
                self.target_location_in_list += 1
                for ele in self.m_ThostFtdc_list:
                    Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\tZeroMemory(&" + ele + ", sizeof(" + ele + "));\n")
                    self.target_location_in_list += 1
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "}\n")
                break
            else:
                self.target_location_in_list += 1
        self.update_file_with_content_list("FemasTHelper.cpp", Modify_FemasTHelper_cpp_content_list)
    
    '''
    update the InitFields
    '''
    def update_InitFields(self):
        Modify_FemasTHelper_cpp_content_list = self.FemasTHelper_cpp_content_list
        self.target_location_in_list = 0
        for line in Modify_FemasTHelper_cpp_content_list:
            if (re.search("InitFields", line) != None):
                self.target_location_in_list += 1
                '''
                clear the current content of InitFields
                '''
                Need_Delete_line = self.target_location_in_list
                while Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}\n" and Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}":
                    Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                
                '''
                insert the updating content into InitFields
                '''
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "{\n")
                self.target_location_in_list += 1
                for ele in self.CThostFtdc_list:
                    if self.Fields_Relation_dict.has_key(ele):
                        for declaration_var_ele in self.Fields_Relation_dict[ele]:
                            Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\tRegField(\"" + ele + "\",\"" + 
                                                                            declaration_var_ele[0] + "\",\"" + declaration_var_ele[1] +
                                                                            "\", \"" + declaration_var_ele[2] + "\", &(" + 
                                                                            self.CThostFtdc_and_mThostFtdc_Relation_dict[ele] + "." + declaration_var_ele[2]
                                                                            + "));\n")
                            self.target_location_in_list += 1
                        Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\n")
                        self.target_location_in_list += 1
                    else:
                        print "Extract ThostFtdcUserApiStruct.h Error"
                        return False
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "}\n")
                break
            else:
                self.target_location_in_list += 1
                
        self.update_file_with_content_list("FemasTHelper.cpp", Modify_FemasTHelper_cpp_content_list)
        
    '''
    update InitFunctions
    '''
    def update_InitFunctions(self):
        Modify_FemasTHelper_cpp_content_list = self.FemasTHelper_cpp_content_list
        self.target_location_in_list = 0
        for line in Modify_FemasTHelper_cpp_content_list:
            if re.search("InitFunctions", line) != None:
                self.target_location_in_list += 1
                '''
                clear the current content of InitFunctions
                '''
                Need_Delete_line = self.target_location_in_list
                while Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}\n" and Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}":
                    Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                
                '''
                insert the updating content into InitFunctions
                '''
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "{\n")
                self.target_location_in_list += 1
                for function_ele in self.Req_Functions_list:
                    if self.Functions_Relation_dict.has_key(function_ele):
                        Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\tRegFun(m_pMainDlg->m_pList->InsertString(-1, \"" + self.Functions_Relation_dict[function_ele][0] +
                                                                        "\"), \"" + function_ele + "\", std::function<int(int)>(std::bind(&CThostFtdcTraderApi::" + function_ele + ", m_pTraderApi, &" + 
                                                                        self.CThostFtdc_and_mThostFtdc_Relation_dict[self.Functions_Relation_dict[function_ele][1]] + ", std::placeholders::_1)), \""
                                                                        + self.Functions_Relation_dict[function_ele][1] + "\");\n")
                        self.target_location_in_list += 1
                    else:
                        print "Extract ThostFtdcTraderApi.h Error"
                        return False
                Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "}\n")
                break
            else:
                self.target_location_in_list += 1
        
        self.update_file_with_content_list("FemasTHelper.cpp", Modify_FemasTHelper_cpp_content_list)
        
    '''
    update the OnSpiDialogMsg
    '''
    def update_OnSpiDialogMsg(self):
        Modify_FemasTHelper_cpp_content_list = self.FemasTHelper_cpp_content_list
        self.target_location_in_list = 0
        for line in Modify_FemasTHelper_cpp_content_list:
            if re.search("OnSpiDialogMsg", line) != None:
                self.target_location_in_list += 1
                '''
                clear the current content of OnSpiDialogMsg
                '''
                Second_start = self.target_location_in_list
                for function_line in Modify_FemasTHelper_cpp_content_list[Second_start : ]:
                    if re.search("\tswitch\(pSpiMsg->m_MsgType\)\n", function_line) != None:
                        self.target_location_in_list += 1
                        Need_Delete_line = self.target_location_in_list
                        while Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "\tdefault:\n":
                            Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
#                        Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                        
                        '''
                        insert the updating content into OnSpiDialogMsg
                        '''
                        Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\t{\n")
                        self.target_location_in_list += 1
                        for function_ele in self.Call_Back_Functions_list:
                            Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\tcase SPI::" + function_ele + ":\n")
                            self.target_location_in_list += 1
                            Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\t\t" + function_ele + "(pSpiMsg);\n")
                            self.target_location_in_list += 1
                            Modify_FemasTHelper_cpp_content_list.insert(self.target_location_in_list, "\t\tbreak;\n")
                            self.target_location_in_list += 1
                        break
                    else:
                        self.target_location_in_list += 1
                break
            else:
                self.target_location_in_list += 1
                
        self.update_file_with_content_list("FemasTHelper.cpp", Modify_FemasTHelper_cpp_content_list)
        
    def clear_existing_call_back_functions_in_FemasTHelper_cpp(self):
        Modify_FemasTHelper_cpp_content_list = self.FemasTHelper_cpp_content_list
        self.target_location_in_list = 0
        for line in Modify_FemasTHelper_cpp_content_list:
            existing_call_back_function_match_object = re.search("void CFemasTHelper::(On[Rsp|Rtn|Err]\w+)", line)
            if existing_call_back_function_match_object != None and existing_call_back_function_match_object.group(1) in self.Call_Back_Functions_list:
                Need_Delete_line = self.target_location_in_list
                while Modify_FemasTHelper_cpp_content_list[Need_Delete_line] != "}\n":
                    Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                Modify_FemasTHelper_cpp_content_list.pop(Need_Delete_line)
                self.target_location_in_list += 1
            else:
                self.target_location_in_list += 1
        self.update_file_with_content_list("FemasTHelper.cpp", Modify_FemasTHelper_cpp_content_list) 
    
    def update_call_back_functions_in_FemasTHelper_cpp(self):
        self.FemasTHelper_cpp_content_list = []
        self.transition_content_in_file_to_list("FemasTHelper.cpp", self.FemasTHelper_cpp_content_list)
        self.target_location_in_list = 0
        for call_back_function in self.Call_Back_Functions_list:
            self.FemasTHelper_cpp_content_list.append("void CFemasTHelper::" + call_back_function + "( CThostSpiMessage *pSpiMsg )\n")
            self.FemasTHelper_cpp_content_list.append("{\n")
            self.FemasTHelper_cpp_content_list.append("\tint nRequestID = pSpiMsg->m_RequestID;\n")
            self.FemasTHelper_cpp_content_list.append("\tbool bIsLast = pSpiMsg->m_bIsLast;\n")
            self.FemasTHelper_cpp_content_list.append("\tPrintHead(\""+ self.Call_Back_Function_and_param_dict[call_back_function][-1] + "\", \"" + call_back_function + "\",nRequestID , bIsLast);\n")
            self.FemasTHelper_cpp_content_list.append("\t" + (re.search("(\w+)[' ''*']+(\w+)", self.Call_Back_Function_and_param_dict[call_back_function][0])).group(1) + " *field = pSpiMsg->GetFieldPtr<" +
                                                      (re.search("(\w+)[' ''*']+(\w+)", self.Call_Back_Function_and_param_dict[call_back_function][0])).group(1) + ">();\n")
            self.FemasTHelper_cpp_content_list.append("\tif (field)\n") 
            self.FemasTHelper_cpp_content_list.append("\t{\n")
            self.FemasTHelper_cpp_content_list.append("\t\tmemcpy(&" + self.CThostFtdc_and_mThostFtdc_Relation_dict[(re.search("(\w+)[' ''*']+(\w+)", self.Call_Back_Function_and_param_dict[call_back_function][0])).group(1)] + 
                                                      ", field, sizeof(" + (re.search("(\w+)[' ''*']+(\w+)", self.Call_Back_Function_and_param_dict[call_back_function][0])).group(1) + "));\n")
            self.FemasTHelper_cpp_content_list.append("\t\tDumpCThostFtdcField(\"" + (re.search("(\w+)[' ''*']+(\w+)", self.Call_Back_Function_and_param_dict[call_back_function][0])).group(1) + 
                                                      "\");\n")
            self.FemasTHelper_cpp_content_list.append("\t}\n")
            self.FemasTHelper_cpp_content_list.append("\tPrintCThostFtdcRspInfoField(&pSpiMsg->m_RspInfo);\n")
            self.FemasTHelper_cpp_content_list.append("}\n\n")
            
        self.update_file_with_content_list("FemasTHelper.cpp", self.FemasTHelper_cpp_content_list)
            
        
    def update_FemasTHelper_cpp(self):
        self.FemasTHelper_cpp_content_list = []
        self.transition_content_in_file_to_list("FemasTHelper.cpp", self.FemasTHelper_cpp_content_list)
        self.update_InitMembers()
        self.update_InitFields()
        self.update_InitFunctions()
        self.update_OnSpiDialogMsg()
        self.clear_existing_call_back_functions_in_FemasTHelper_cpp()
        self.update_call_back_functions_in_FemasTHelper_cpp()
    
    
    
if __name__ == '__main__':
    ctp_handler = batch_handler()
    #对ThostFtdcUserApiStruct.h文件进行解析
    ctp_handler.extract_cthostftdc_fields_from_api_struct()
    #对ThostFtdcTraderApi.h文件进行解析
    ctp_handler.extract_callback_functions_and_reqfunctions_from_trade_api()
    #更新FemasTHelper.h文件
    ctp_handler.update_FemasTHelper_h()
    #更新FemasSpiMessage.h文件
    ctp_handler.update_FemasSpiMessage_h()
    #更新TraderFemasHandler.h文件
    ctp_handler.update_TraderFemasHandler_h()
    #更新FemasTHelper.cpp文件
    ctp_handler.update_FemasTHelper_cpp()
    
    
    print "File Processing End!"