#include "PROTOTYPES.h"
#include "String_Functions.h"
Token Collect(const char* string, char op1, char op2, size_t start){
	size_t i, j, v=0, B=0;
  if((op1 == '{' && op2 == '}') || (op1 == ':' && op2 == '.')) B = 1;
	Token collect = {.sz = 1, .contents = (char*)malloc(collect.sz)};
	for(i = start, j = 0, v = 0;  string[i] != '\0'; i++){
		if(collect.beg){
      if(B) v += string[i] == op1;
			if(collect.sz <= j) 
				collect.contents = (char*)realloc(collect.contents, ++collect.sz);
			if(string[i] == op2 && !(v--)){
				collect.end  = op2, collect.closing = i;
				break;
			}
			collect.contents[j++] = string[i];
			continue;
		}
		if(string[i] == op1)
			collect.beg = op1, collect.opening = i;
	}
	collect.contents[j] = '\0';
	return collect;
}

void Basic_Syntax(char character, char* storage, long* index, long mcapacity){
	switch(character){
		case '>':
			if(*index+1 >= mcapacity) ERROR(INDEX_ERROR);
			++*index;
			break;
		case '<':
			if(*index-1 < 0) ERROR(INDEX_ERROR);
			--*index;
			break;
		case '+':
			if(storage[*index]+1 > 127) ERROR(BYTE_ERROR);
      storage[*index]++;
			break;
		case '-':
      if(storage[*index]-1 < -128) ERROR(BYTE_ERROR);
			storage[*index]--;
			break;
		case '$':
			storage[*index] = getchar();
			break;
		case 'c':
		case 'C':
			printf("%c", storage[*index]);
			break;
		case 'd':
		case 'D':
			printf("%d", storage[*index]);
			break;
		case 's':
		case 'S':
			printf("%s", storage);
			break;
    
	}
}


void Complex_Syntax(char character, char* code, char** storage, long* storageindex, size_t* i, long* mcapacity){
	Token token = {}, token2 = {}; long v = 0;
		switch(character){
			case '[':
				token = Collect(code, '[', ']', *i);
				if(token.beg&&token.end){
          free(*storage);
					*storage = (char*)calloc(sizeof(char), *mcapacity=atoi(token.contents));
					memset(*storage, 0, *mcapacity); // Just in case
          *storageindex = 0;
				} else ERROR(SYNTAX_ERROR);
        free(token.contents);
				break;
      case ';':
        if(code[*i] == ';')
			    *i = ((v = ffo(code, *i, "\n"))!=-1) ? v:*i;
        return;
      case '#':
        token = Collect(code, '#', '#', *i);
        if(token.beg&&token.end){
          int tph = atoi(token.contents);
          if(tph > *mcapacity-1) ERROR(INDEX_ERROR);
          *storageindex = atoi(token.contents);
        }
        free(token.contents);
        break;
			case '(':
				token = Collect(code, '(', ')', *i);
				if(token.beg&&token.end){
					char C; int D;
					sscanf(token.contents, "%c%d", &C, &D);
					D = (D||C=='#'||C=='=') ? D: *(*storage+*storageindex);
					switch(C){
						case '*':
              if(*(*storage+*storageindex)*D > 127||
              *(*storage+*storageindex)*D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageindex) *= D;
							break;
						case '/':
              if(*(*storage+*storageindex)/D > 127||
              *(*storage+*storageindex)/D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageindex) /= D;
							break;
						case '+':
              if(*(*storage+*storageindex)+D > 127) ERROR(BYTE_ERROR);
							*(*storage+*storageindex) += D;
							break;
						case '-':
              if(*(*storage+*storageindex)-D < -128) ERROR(BYTE_ERROR);
							*(*storage+*storageindex) -= D;
							break;
            case '#':
              if(D > *mcapacity-1||D<=-1) ERROR(INDEX_ERROR);
              *(*storage+*storageindex) = *(*storage+D);
              break;
            case '>':
              if(D > *mcapacity-1) ERROR(INDEX_ERROR);
              *storageindex += D;
              break;
            case '<':
              if(D <= -1) ERROR(INDEX_ERROR);
              *storageindex += D;
              break;
            // From this point is a modification
            case '=':
              token2 = Collect(code, ':', '.', token.closing);
              if(token2.beg&&token2.end){
                //printf("<p>%s</p>", token2.contents);
                if(*(*storage+*storageindex) == D){
                  for(size_t X = 0; token2.contents[X]; X++){
						        Basic_Syntax(token2.contents[X], *storage, storageindex, *mcapacity);
                    Complex_Syntax(token2.contents[X], token2.contents, storage, storageindex, &X, mcapacity);
                  }
                }
              }
              free(token2.contents);
              *i = token2.closing;
              return;
            // End of modification
						default:
              ERROR(SYNTAX_ERROR);
              break;
					}
				} else ERROR(SYNTAX_ERROR);
        free(token.contents);
				break;	
			case '{':
				token = Collect(code, '{', '}', *i);
        if(token.beg&&token.end){
          while(*(*storage+*storageindex)){
            for(size_t X = 0; token.contents[X]; X++){
              if(token.contents[X] == ';')
							  ERROR(SYNTAX_ERROR);
						  Basic_Syntax(token.contents[X], *storage, storageindex, *mcapacity);
              Complex_Syntax(token.contents[X], token.contents, storage, storageindex, &X, mcapacity);
            }
          }
        } else ERROR(SYNTAX_ERROR);
        free(token.contents);
				break;
		}
    if(token.closing) *i = token.closing;
}
