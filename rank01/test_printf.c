#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <limits.h>

static void print_nl(void)
{
	printf("\n");
}

static void print_compare(int output_og, int output_ft, char *test_name)
{
	printf("Value OG: %d\n", output_og);
	printf("Value FT: %d\n", output_ft);
	if (output_og == output_ft)
		printf("SIZE OK in %s! ✅\n", test_name);
	else
		printf("SIZE ERROR in %s! ❌\n", test_name);
}

static void test_no_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== NO CONVERSION ======\n");
	output_og = printf("#1 OG -> Test String \t TEeeEEEeEEsT String\n");
	output_ft = ft_printf("#1 FT -> Test String \t TEeeEEEeEEsT String\n");
	print_compare(output_og, output_ft, "NO CONVERSION #1");
	print_nl();
	output_og = printf("#2 OG -> T \t t \n");
	output_ft = ft_printf("#2 FT -> T \t t \n");
	print_compare(output_og, output_ft, "NO CONVERSION #2");
	print_nl();
}

static void test_c_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%c ======\n");
	output_og = printf("%c\n", 'C');
	output_ft = ft_printf("%c\n", 'C');
	print_compare(output_og, output_ft, "CONVERSION %%c #1");
	print_nl();
	output_og = printf("My favorite language is: %c\n", 'C');
	output_ft = ft_printf("My favorite language is: %c\n", 'C');
	print_compare(output_og, output_ft, "CONVERSION %%c #2");
	print_nl();
	output_og = printf("Larger than char: %c\n", 'C' + 1024);
	output_ft = ft_printf("Larger than char: %c\n", 'C' + 1024);
	print_compare(output_og, output_ft, "CONVERSION %%c #3");
	print_nl();
	output_og = printf("Testing NULL: %c\n", 0);
	output_ft = ft_printf("Testing NULL: %c\n", 0);
	print_compare(output_og, output_ft, "CONVERSION %%c #4");
	print_nl();
	output_og = printf("TESTING BELL (Non-printable): %c\n", 7);
	output_ft = ft_printf("TESTING BELL (Non-printable): %c\n", 7);
	print_compare(output_og, output_ft, "CONVERSION %%c #5");
	print_nl();
	output_og = printf("Several Chars: %c-%c-%c\n", '0',0,'7');
	output_ft = ft_printf("Several Chars: %c-%c-%c\n", '0',0,'7');
	print_compare(output_og, output_ft, "CONVERSION %%c #6");
	print_nl();
	output_og = printf("Several Chars: %c%c%c\n", '0',0,'7');
	output_ft = ft_printf("Several Chars: %c%c%c\n", '0',0,'7');
	print_compare(output_og, output_ft, "CONVERSION %%c #6");
	print_nl();
}

static void test_s_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%s ======\n");
	output_og = printf("%s\n", "Simple String");
	output_ft = ft_printf("%s\n", "Simple String");
	print_compare(output_og, output_ft, "CONVERSION %%s #1");
	print_nl();
	output_og = printf("My favorite language is: %s\n", "Javascript");
	output_ft = ft_printf("My favorite language is: %s\n", "Javascript");
	print_compare(output_og, output_ft, "CONVERSION %%s #2");
	print_nl();
	output_og = printf("I'm shocked that this emoji works! %s\n", "😱");
	output_ft = ft_printf("I'm shocked that this emoji works! %s\n", "😱");
	print_compare(output_og, output_ft, "CONVERSION %%s #3");
	print_nl();
	char *nullstr = NULL;
	output_og = printf("This should be NULL: %s\n", nullstr);
	output_ft = ft_printf("This should be NULL: %s\n", nullstr);
	print_compare(output_og, output_ft, "CONVERSION %%s #4");
	print_nl();
	char *longstr = (char *) ft_memset(ft_calloc(4096, sizeof(char)),'a',4095);
	output_og = printf("%s\n", longstr);
	output_ft = ft_printf("%s\n", longstr);
	print_compare(output_og, output_ft, "CONVERSION %%s #5");
	free(longstr);
	print_nl();
	output_og = printf("%s %s\n", "a", "b");
	output_ft = ft_printf("%s %s\n", "a", "b");
	print_compare(output_og, output_ft, "CONVERSION %%s #6");
	print_nl();
	output_og = printf("%s%s%s\n", "a", "b", "c");
	output_ft = ft_printf("%s%s%s\n", "a", "b", "c");
	print_compare(output_og, output_ft, "CONVERSION %%s #7");
	print_nl();
}

static void test_percent_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %% ======\n");
	output_og = printf("%%\n");
	output_ft = ft_printf("%%\n");
	print_compare(output_og, output_ft, "CONVERSION %% #1");
	print_nl();
	output_og = printf("100%% of 42 is 42!\n");
	output_ft = ft_printf("100%% of 42 is 42!\n");
	print_compare(output_og, output_ft, "CONVERSION %% #2");
	print_nl();
	output_og = printf("100%%%s!\n","of 42 is 42");
	output_ft = ft_printf("100%%%s!\n", "of 42 is 42");
	print_compare(output_og, output_ft, "CONVERSION %% #3");
	print_nl();
	output_og = printf("%d%%%s\n", 100, " of 42 is 42!");
	output_ft = ft_printf("%d%%%s\n", 100, " of 42 is 42!");
	print_compare(output_og, output_ft, "CONVERSION %% #4");
	print_nl();
}

static void test_d_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%d ======\n");
	output_og = printf("%i\n", 123456789);
	output_ft = ft_printf("%i\n", 123456789);
	print_compare(output_og, output_ft, "CONVERSION %d #1");
	print_nl();
	output_og = printf("%i\n", -42);
	output_ft = ft_printf("%i\n", -42);
	print_compare(output_og, output_ft, "CONVERSION %d #2");
	print_nl();
	output_og = printf("%i\n",0);
	output_ft = ft_printf("%i\n",0);
	print_compare(output_og, output_ft, "CONVERSION %d #3");
	print_nl();
	output_og = printf("%i\n", INT_MIN);
	output_ft = ft_printf("%i\n", INT_MIN);
	print_compare(output_og, output_ft, "CONVERSION %d #4");
	print_nl();
	output_og = printf("%i\n", INT_MAX);
	output_ft = ft_printf("%i\n", INT_MAX);
	print_compare(output_og, output_ft, "CONVERSION %d #5");
	print_nl();
	output_og = printf("Hexa: %i\n", 0x42);
	output_ft = ft_printf("Hexa: %i\n", 0x42);
	print_compare(output_og, output_ft, "CONVERSION %d #6");
	print_nl();
	output_og = printf("Octal: %i\n", 042);
	output_ft = ft_printf("Octal: %i\n", 042);
	print_compare(output_og, output_ft, "CONVERSION %d #7");
	print_nl();
}

static void test_i_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%i ======\n");
	output_og = printf("%i\n", 123456789);
	output_ft = ft_printf("%i\n", 123456789);
	print_compare(output_og, output_ft, "CONVERSION %i #1");
	print_nl();
	output_og = printf("%i\n", -42);
	output_ft = ft_printf("%i\n", -42);
	print_compare(output_og, output_ft, "CONVERSION %i #2");
	print_nl();
	output_og = printf("%i\n",0);
	output_ft = ft_printf("%i\n",0);
	print_compare(output_og, output_ft, "CONVERSION %i #3");
	print_nl();
	output_og = printf("%i\n", INT_MIN);
	output_ft = ft_printf("%i\n", INT_MIN);
	print_compare(output_og, output_ft, "CONVERSION %i #4");
	print_nl();
	output_og = printf("%i\n", INT_MAX);
	output_ft = ft_printf("%i\n", INT_MAX);
	print_compare(output_og, output_ft, "CONVERSION %i #5");
	print_nl();
	output_og = printf("Hexa: %i\n", 0x42);
	output_ft = ft_printf("Hexa: %i\n", 0x42);
	print_compare(output_og, output_ft, "CONVERSION %i #6");
	print_nl();
	output_og = printf("Octal: %i\n", 042);
	output_ft = ft_printf("Octal: %i\n", 042);
	print_compare(output_og, output_ft, "CONVERSION %i #7");
	print_nl();
}

static void test_u_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%u ======\n");
	output_og = printf("%u\n", 123456789);
	output_ft = ft_printf("%u\n", 123456789);
	print_compare(output_og, output_ft, "CONVERSION %u #1");
	print_nl();
	output_og = printf("%u\n", -42);
	output_ft = ft_printf("%u\n", -42);
	print_compare(output_og, output_ft, "CONVERSION %u #2");
	print_nl();
	output_og = printf("%u\n",0);
	output_ft = ft_printf("%u\n",0);
	print_compare(output_og, output_ft, "CONVERSION %u #3");
	print_nl();
	output_og = printf("%u\n", INT_MIN);
	output_ft = ft_printf("%u\n", INT_MIN);
	print_compare(output_og, output_ft, "CONVERSION %u #4");
	print_nl();
	output_og = printf("%u\n", INT_MAX);
	output_ft = ft_printf("%u\n", INT_MAX);
	print_compare(output_og, output_ft, "CONVERSION %u #5");
	print_nl();
	output_og = printf("Hexa: %u\n", 0x42);
	output_ft = ft_printf("Hexa: %u\n", 0x42);
	print_compare(output_og, output_ft, "CONVERSION %u #6");
	print_nl();
	output_og = printf("Octal: %u\n", 042);
	output_ft = ft_printf("Octal: %u\n", 042);
	print_compare(output_og, output_ft, "CONVERSION %u #7");
	print_nl();
}

static void test_x_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%x ======\n");
	output_og = printf("%x\n", 123456789);
	output_ft = ft_printf("%x\n", 123456789);
	print_compare(output_og, output_ft, "CONVERSION %x #1");
	print_nl();
	output_og = printf("%x\n", -42);
	output_ft = ft_printf("%x\n", -42);
	print_compare(output_og, output_ft, "CONVERSION %x #2");
	print_nl();
	output_og = printf("%x\n",0);
	output_ft = ft_printf("%x\n",0);
	print_compare(output_og, output_ft, "CONVERSION %x #3");
	print_nl();
	output_og = printf("%x\n", INT_MIN);
	output_ft = ft_printf("%x\n", INT_MIN);
	print_compare(output_og, output_ft, "CONVERSION %x #4");
	print_nl();
	output_og = printf("%x\n", INT_MAX);
	output_ft = ft_printf("%x\n", INT_MAX);
	print_compare(output_og, output_ft, "CONVERSION %x #5");
	print_nl();
	output_og = printf("Hexa: %x\n", 0x42);
	output_ft = ft_printf("Hexa: %x\n", 0x42);
	print_compare(output_og, output_ft, "CONVERSION %x #6");
	print_nl();
	output_og = printf("Octal: %x\n", 042);
	output_ft = ft_printf("Octal: %x\n", 042);
	print_compare(output_og, output_ft, "CONVERSION %x #7");
	print_nl();
}

void test_p_conversion(void)
{
	int	output_og;
	int	output_ft;

	printf("====== CONVERSION: %%p ======\n");
	output_og = printf("%p\n", &output_og);
	output_ft = ft_printf("%p\n", &output_og);
	print_compare(output_og, output_ft, "CONVERSION %x #1");
	print_nl();
	output_og = printf("%p\n", NULL );
	output_ft = ft_printf("%p\n", NULL);
	print_compare(output_og, output_ft, "CONVERSION %x #1");
	print_nl();
}

int main(void)
{
	// NO CONVERSION
	test_no_conversion();
	// testing %c
	test_c_conversion();
	// testing %d
	test_d_conversion();
	// testing %i
	test_i_conversion();
	// testing %u
	test_u_conversion();
	// testing %x
	test_x_conversion();
	// testing %%
	test_percent_conversion();
	// testing %s
	test_s_conversion();
	// testing %p
	test_p_conversion();
	return (0);
}
