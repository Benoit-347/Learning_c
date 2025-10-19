
def transpose(nested_list):
    new_list = []
    len_list = len(nested_list[0])
    for i in range(len_list):
        list_temp = []
        for list_1 in nested_list:
            list_temp.append(list_1[i])
        new_list.append(list_temp)
    return new_list
      