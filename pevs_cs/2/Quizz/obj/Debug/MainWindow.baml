   M S B A M L   `   `   `  ����@  <Quizz, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:QuizzQuizz  5   	       Quizz.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   %localclr-namespace:Quizz     5   	   U QMaterialDesignThemes.Wpf, Version=3.0.1.920, Culture=neutral, PublicKeyToken=nullFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5   	   ���#333333   MaterialDesignBody#���   5
   	     � WindowStartupLocation$  CenterScreen=�5   	    � Title$ Quizz��5   	   $	��450��6   $	��800��6'    � 
ResizeMode$ 	CanResize=�66   $	��450��6M   $	��800��6Y    � 	Resources 5      '   !Quizz.EnumMatchToBooleanConverter  enumConverter �� 
TargetType �� Property �� Value �� 
TargetType �� 
Background	 � Cursor
 �� Bullet �� CornerRadius �� Triggers P� Property P� Value �� 
TargetName��%�  &	       '	�        5   
   6,   �� 5   
   " 	�6   .�5      ��  � �� 5      �� 5      " 	�6&   .R�5      �� 
 ���� $
	 Hand��6C   
 5      � 5   "   $��30��6'   $��30��63   .+�5   &   �� $��
RadioOuter��6-   
������ 
�������$��2q�6p   $ 2��6�   �� 5   &   $��	RadioMark��6I   $ 0��6-   $��4q�6>   ���	#FF673AB7$y�Hidden=�6q   5   #   ._�5      �� $��8,1,0,0q�6(   
�������$��Calibri)�6L   $��22(�6a   �� 5   "   5      5       5      P� 5       �@d�	IsChecked$
 trueY�6;   . �5    "   �� $ 	RadioMark��6)    � y�$ Visible=�6V   �� 5!   "   $ 
RadioOuter��6)    � �� �#ff661a6X   5"      5$      5&      5'      5(      .��5)      �  � RowDefinitions 5*   
   �� 5+      $
��auto �6   �� 5,      $��* �6   �� 5-      $
��auto �6   �� 5.      $
��auto �6   .+�50   
   #  MaterialDesignThemes.Wpf.Card  $��32q�6   $��16q�6+   $��0��67   
���iii�.��51      ]� .+�52      �� 
�������$��25(�6J   $
��Bold"�6X   ��6   �� *	QuizzName+6X   �� 53      $��1��6    �� Orientation$ 
Horizontal=�6*   $��Right=�6C   .+�54      �� $��	Question ��6    
�������$��25(�6D   �� 55      
�������$��25(�63   ��56      `� 57       �� StringFormat$ {0}/{1}��6+   .1�58   "   ��  �� Path$ 
QuestionNr�6*   �� 59   "   $ QuestionCnt�6*   5:      5<      5=      5>      5?      �� 5@   
   $��1��6   $��50q�6$   $
��Auto=�60   $��Disabled=�6S   .��5A      �� 
�������$��25(�6+   $
��Wrap=�69   �� 5B      �6   �� *QuestionText+�� 5C      �� 5D      �� 5E      $	�A) ��6    �� 5F      �6   �� *QuestionOptionA+�� 5G      �� 5H      $	�B) ��6    �� 5I      �6   �� *QuestionOptionB+�� 5J      �� 5K      $	�C) ��6    �� 5L      �6   �� *QuestionOptionC+�� 5M      �� 5N      $	�D) ��6    �� 5O      �6   �� *QuestionOptionD+5P      5Q      �� 5R   
   $��2��6   $ 
Horizontal=�6"   $
��0 20q�6;   $��Right=�6I   .+�5S      	�  	� 	GroupName$ q��6   $��A��6(   $
��20 0q�64    d� 	IsChecked 6B   �� $ CurrentOption� �� Mode$ TwoWay=� �� 	Converter# [  �� ConverterParameter$ OptionA��	� 5T      $ q��6   $��B��6(   $
��20 0q�64    6B   �� $ CurrentOption�$ TwoWay=�# [ $ OptionB��	� 5U      $ q��6   $��C��6(   $
��20 0q�64    6B   �� $ CurrentOption�$ TwoWay=�# [ $ OptionC��	� 5V      $ q��6   $��D��6(   $
��20 0q�64    6B   �� $ CurrentOption�$ TwoWay=�# [ $ OptionD��5W      �� 5X   
   $��0q�6   $��3��6%   $��Bottom=�62    J� Effect 5Y      3  -System.Windows.Media.Effects.DropShadowEffect  5Z         Color$
 Gray��6#      	Direction$	 160Q�60   ._�5\      ]� ���#ff661a.+�5]      ]� $��	16 5 16 5q�6   .+�5^      �� $��CLEAR��6   ��6-   �� $ clearCommand��� 5_      $��
LOAD QUIZZ��6   $
��10 0q�6W   ��62   �� $ loadCommand�6W   �� 5`      $ 
Horizontal=�6!   $��Right=�6:   .+�5a      �� $
��10 0q�6|   ��6!   0  *MaterialDesignThemes.Wpf.PackIconExtension  *ArrowLeftBold+��6S   �� $ previousCommand�6|   �� 5b      ��6!     *ArrowRightBold+��6T   �� $ nextCommand�5c      5d      5e      5f      5i      5j      