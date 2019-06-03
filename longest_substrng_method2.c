int lengthOfLongestSubstring(char * s)
{
    if (s == NULL || s[0] == '\0')
        return 0;
    
    bool list[128] = { false };
    int length = 1;
    int max = length;
    char * head = s;
    char * tail = s + 1;
    
    list[*head] = true;
    while (*tail != NULL)
    {
        if (list[*tail] == false)
        {
            list[*tail] = true;
            if (++length > max)
                max = length;
        }
        else
        {
            while(head < tail)
            {
                if (*head == *tail)
                {
                    head++;
                    break;
                }
                list[*head] = false;
                --length;
                head++;
            }
        }
        tail++;
    }
    return max;
}