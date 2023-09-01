char * longestCommonPrefix(char ** strs, int strsSize){
    for(int j=0;strs[0][j] != '\0' ; j++){
        for(int i = 1; i < strsSize; i++){
            if(strs[i][j] != strs[0][j]){
                strs[0][j] = '\0';
                return strs[0];
            }
        }
    }
    return strs[0];
}
