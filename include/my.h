/*
** my.h for N4S in /home/Rubiks/CPE/CPE_2016_n4s/CPE_2016_n4s
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Sun May  7 19:10:06 2017 Maxime BLANCHARD
** Last update Thu May 11 17:59:08 2017 Maxime BLANCHARD
*/

#ifndef MY_H_
# define MY_H_

# include <stdbool.h>

#define LEFT lidar->left
#define M_LEFT lidar->m_left
#define MID lidar->middle
#define M_RIGHT lidar->m_right
#define RIGHT lidar->right

#define STEP_SIZE 100
#define ANGLE_SIZE 0.02
#define MAX_DETECT 970

#define MIN_SPEED 0.19
#define BRAKE 0.1

#define DIR_R -1
#define DIR_L 1

#define NONE_VAR 0
#define F_VAR 1
#define I_VAR 2
#define TRUE 1
#define FALSE 0

typedef enum	e_actions
  {
    START_SIMULATION, STOP_SIMULATION, CAR_FORWARD, CAR_BACKWARDS,
    WHEELS_DIR, GET_INFO_LIDAR, GET_CURRENT_SPEED, GET_CURRENT_WHEELS,
    CYCLE_WAIT, GET_CAR_SPEED_MAX, GET_CAR_SPEED_MIN, GET_INFO_SIMTIME
  }		t_actions;

typedef struct          s_info_sim
{
  double                speed;
  double                wheels;
}                       t_info_sim;

typedef struct  s_info_lidar
{
  double        left;
  double        m_left;
  double        middle;
  double        m_right;
  double        right;
}               t_info_lidar;

typedef struct		s_memory
{
  t_info_lidar		*lidar;
  double		angle;
  double		speed;
  struct s_memory	*next;
}			t_memory;

typedef struct  s_command
{
  char  *cmd;
  int   var_type;
  int   answer_type;
}               t_command;

typedef struct  s_ans2
{
  double        infos[32];
}               t_ans2;

typedef struct  s_ans3
{
  double        speed;
}               t_ans3;

typedef struct  s_ans4
{
  long long     time_sec;
  long long     time_ns;
}               t_ans4;

typedef struct  s_answer
{
  int           type;
  int           value_id;
  bool          status;
  char          *code_str;
  char          *additionnal_info;
  t_ans2        *ans2;
  t_ans3        *ans3;
  t_ans4        *ans4;
}               t_answer;

extern t_command	g_commands[13];
extern double		g_speed;
extern t_memory		*g_memory;
extern double		g_wheels;

double		calc_wheels(t_info_lidar *);
void		brakes(double);
int		new_direction(t_info_lidar *, int);
t_memory        *i_gmemdir(t_memory *, double *, double *, double *);
void		show_memory(t_memory *);
int		my_strlen(char *);
void		set_direction(t_info_lidar *);
int		detect_col(double *);
int		do_average(double *, int, int);
t_memory	*load_memory(char *);
void		correct_memory(t_info_lidar *, t_info_lidar **, int);
double		get_memory_dir(t_memory *, t_info_lidar *, double *);
int		stabilizator(int);
int		my_strcmp(char *, char *);
char		**str_to_wordtab(char *, char *);
int		direction(t_info_lidar *, int);
t_info_lidar	*dup_lidar(t_info_lidar *);
int		check_memory_dup(t_memory *, t_info_lidar *, double);
t_memory	*add_memory(t_memory *, t_info_lidar *, double, double);
void		set_speed(double);
void		display_radar(double *);
t_answer	*exec_instruction(int, ...);
bool		get_status(char *);
t_answer	*get_answer(char *, int);
long long	get_long(char *);
char	*my_itoa(int);
char	*my_ltoa(long long);
char	*my_ftoa(double);
char	*get_next_line(const int);
double	get_double(char *);
char	*my_ftoa(double);
void	print_answer(t_answer *);
#endif
