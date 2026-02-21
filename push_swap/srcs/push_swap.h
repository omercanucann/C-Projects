/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:52:05 by oucan             #+#    #+#             */
/*   Updated: 2025/03/09 19:12:19 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	long			nbr;
	long			index;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

void		list_args(char **argv, t_stack **stack_a);
void		ft_add_back(t_stack **stack, t_stack *stack_new);
int			ft_atoitwo(const char *str, t_stack *a);
t_stack		*ft_stack_new(int content);
int			ft_checkduplicate(t_stack *a);
void		ft_error(t_stack *a);
void		ft_errortwo(t_stack *a, char **temp);
void		ft_free(t_stack **lst);
t_stack		*ft_lstlast(t_stack *lst);
void		ft_ra(t_stack **a);
void		ft_rb(t_stack **b);
void		ft_sa(t_stack **a);
void		ft_pa(t_stack **a, t_stack **b);
void		ft_pb(t_stack **stack_a, t_stack **stack_b);
void		ft_rra(t_stack **a);
void		ft_ss(t_stack **a, t_stack **b, int j);
void		ft_rr(t_stack **a, t_stack **b);
void		ft_rrr_sub(t_stack **b);
void		ft_rrr(t_stack **a, t_stack **b);
int			ft_lstsize(t_stack *lst);
int			ft_minimum(t_stack *a);
int			ft_maximum(t_stack *a);
int			ft_find_index(t_stack *a, int nbr);
int			ft_find_place_b(t_stack *stack_b, int nbr_push);
int			ft_find_place_a(t_stack *a, int nbr);
void		ft_sort(t_stack **stack_a);
int			ft_checksorted(t_stack *stack_a);
void		ft_sort_three(t_stack **stack_a);
t_stack		*ft_separate(int argc, char **argv);
t_stack		*ft_separate_args(char **argv);
void		ft_freestr(char **lst);
int			ft_case_rarb_a(t_stack *a, t_stack *b, int c);
int			ft_case_rrarrb_a(t_stack *a, t_stack *b, int c);
int			ft_case_rarrb_a(t_stack *a, t_stack *b, int c);
int			ft_case_rrarb_a(t_stack *a, t_stack *b, int c);
int			ft_case_rarb(t_stack *a, t_stack *b, int c);
int			ft_case_rrarrb(t_stack *a, t_stack *b, int c);
int			ft_case_rrarb(t_stack *a, t_stack *b, int c);
int			ft_case_rarrb(t_stack *a, t_stack *b, int c);
int			ft_rotate_ab(t_stack *a, t_stack *b);
int			ft_rotate_ba(t_stack *a, t_stack *b);
int			ft_put_rarb(t_stack **a, t_stack **b, int c, char s);
int			ft_put_rrarrb(t_stack **a, t_stack **b, int c, char s);
int			ft_put_rrarb(t_stack **a, t_stack **b, int c, char s);
int			ft_put_rarrb(t_stack **a, t_stack **b, int c, char s);
void		ft_rrb(t_stack **b);
t_stack		*ft_processing(int argc, char **argv);
void		ft_sb(t_stack **b, int j);
void		ft_sort_b_until_three(t_stack **stack_a, t_stack **stack_b);
t_stack		*ft_sub_processing(char **argv);
int			ft_process_rotation(t_stack **stack_a, t_stack **stack_b,
				t_stack *tmp, int i);
int			ft_process_rotation_a(t_stack **stack_a, t_stack **stack_b,
				t_stack *tmp, int i);
#endif