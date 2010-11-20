VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H00FFFFFF&
   Caption         =   "点阵模拟程序"
   ClientHeight    =   12135
   ClientLeft      =   165
   ClientTop       =   525
   ClientWidth     =   11430
   FillColor       =   &H000000FF&
   ForeColor       =   &H000000FF&
   LinkTopic       =   "Form1"
   ScaleHeight     =   12135
   ScaleWidth      =   11430
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command3 
      Caption         =   "找点"
      Height          =   375
      Left            =   9960
      TabIndex        =   5
      Top             =   600
      Width           =   975
   End
   Begin VB.TextBox y 
      Height          =   375
      Left            =   10560
      TabIndex        =   4
      Top             =   120
      Width           =   375
   End
   Begin VB.TextBox x 
      Height          =   375
      Left            =   9960
      TabIndex        =   3
      Top             =   120
      Width           =   375
   End
   Begin VB.CommandButton Command2 
      Caption         =   "撤销"
      Height          =   495
      Left            =   10200
      TabIndex        =   2
      Top             =   10800
      Width           =   855
   End
   Begin VB.CommandButton Pt 
      BackColor       =   &H00000000&
      Height          =   300
      Index           =   0
      Left            =   0
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   0
      Width           =   300
   End
   Begin VB.CommandButton Command1 
      Caption         =   "清空"
      Height          =   495
      Left            =   10200
      TabIndex        =   0
      Top             =   10080
      Width           =   855
   End
   Begin VB.Menu Popmenu 
      Caption         =   "PopMenu"
      Visible         =   0   'False
      Begin VB.Menu 生成代码 
         Caption         =   "生成代码"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim znum As Integer


Private Sub Command1_Click()
Dim x As Integer
Dim y As Integer
Dim num As Integer
Pt(0).ToolTipText = "x: 0,y: 0"
For y = 0 To 35
    For x = 0 To 31
        If x <> 0 Or y <> 0 Then
            num = y * 32 + x
            If x = 0 Or x = 7 Or x = 8 Or x = 15 Or x = 16 Or x = 23 Or x = 24 Or x = 31 Or y = 0 Or y = 8 Or y = 9 Or y = 17 Or y = 18 Or y = 26 Or y = 27 Or y = 35 Then
            Pt(num).BackColor = 16744703
            Else
            Pt(num).BackColor = 0
            End If
        End If
    Next
Next
End Sub

Private Sub Command2_Click()
If znum <> 10000 Then
Pt(znum).BackColor = 16777215 - Pt(znum).BackColor
    
End If

End Sub

Public Sub Command3_Click()
Dim index As Integer
index = 32 * CInt(y.Text) + CInt(x.Text)


Pt(index).BackColor = 16777215 - Pt(index).BackColor

znum = index





End Sub

Private Sub Form_Load()
Dim x As Integer
Dim y As Integer
Dim num As Integer
Pt(0).ToolTipText = "x: 0,y: 0"
For y = 0 To 35
    For x = 0 To 31
        If x <> 0 Or y <> 0 Then
            
            num = y * 32 + x
            Load Pt(num)
            Pt(num).Top = y * 300
            Pt(num).Left = x * 300
            Pt(num).Height = 300
            Pt(num).Width = 300
            Pt(num).Visible = True
            Pt(num).Enabled = True
            Pt(num).ToolTipText = "x:" + Str(x) + ",y:" + Str(y)
            If x = 0 Or x = 7 Or x = 8 Or x = 15 Or x = 16 Or x = 23 Or x = 24 Or x = 31 Or y = 0 Or y = 8 Or y = 9 Or y = 17 Or y = 18 Or y = 26 Or y = 27 Or y = 35 Then
            Pt(num).BackColor = 16744703
            End If
            
        End If
    Next
Next
Pt(0).BackColor = 16744703


End Sub

Private Sub Pt_MouseDown(index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
If Button = 1 Then
    

    Pt(index).BackColor = 16777215 - Pt(index).BackColor

    znum = index
End If

If Button = 2 Then
Indexshowpt = index
Pt(index).SetFocus
PopupMenu Popmenu

End If

End Sub

Private Sub x_GotFocus()
x.Text = ""
End Sub

Private Sub x_KeyPress(KeyAscii As Integer)
If KeyAscii = 13 Then
y.SetFocus
End If

End Sub

Private Sub y_GotFocus()
y.Text = ""


End Sub

Private Sub y_KeyPress(KeyAscii As Integer)
If KeyAscii = 13 Then
x.SetFocus
Form1.Command3_Click
End If
End Sub

Private Sub 生成代码_Click()


ShowPt.Visible = True
End Sub
