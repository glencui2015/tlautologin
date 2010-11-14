VERSION 5.00
Begin VB.Form ShowPt 
   Caption         =   "点图坐标偏移"
   ClientHeight    =   4890
   ClientLeft      =   60
   ClientTop       =   420
   ClientWidth     =   9930
   LinkTopic       =   "Form2"
   ScaleHeight     =   4890
   ScaleWidth      =   9930
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   8280
      TabIndex        =   1
      Top             =   4440
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   4335
      Left            =   0
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   0
      Width           =   9855
   End
End
Attribute VB_Name = "ShowPt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Unload Me

End Sub

Private Sub Form_Load()
Dim X As Integer
Dim Y As Integer
Dim mx As Integer
Dim my As Integer
Dim fx As String
Dim fy As String
Dim num As Integer
MsgBox Str(Indexshowpt)

my = Indexshowpt \ 32
mx = Indexshowpt Mod 32
MsgBox Str(my) + Str(mx)

For Y = 0 To 35
    For X = 0 To 31
        If X <> 0 Or Y <> 0 Then
            num = Y * 32 + X
            If Form1.Pt(num).BackColor = 255 Then
                If Y - my < 0 Then
                fy = ""
                Else
                fy = "+"
                End If
                
                If X - mx < 0 Then
                fx = ""
                Else
                fx = "+"
                End If
                
                ShowPt.Text1.Text = ShowPt.Text1.Text + "this->BO[n][y" + fy + Trim(Str(Y - my)) + "][x" + fx + Trim(Str(X - mx)) + "] && "
            End If
        End If
    Next
Next
End Sub

