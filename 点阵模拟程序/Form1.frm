VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H00FFFFFF&
   Caption         =   "点阵模拟程序"
   ClientHeight    =   12135
   ClientLeft      =   165
   ClientTop       =   825
   ClientWidth     =   11430
   FillColor       =   &H000000FF&
   ForeColor       =   &H000000FF&
   LinkTopic       =   "Form1"
   ScaleHeight     =   12135
   ScaleWidth      =   11430
   StartUpPosition =   3  '窗口缺省
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
Dim X As Integer
Dim Y As Integer
Dim num As Integer
Pt(0).ToolTipText = "x: 0,y: 0"
For Y = 0 To 35
    For X = 0 To 31
            num = Y * 32 + X
            Pt(num).BackColor = 0
    Next
    

Next
End Sub

Private Sub Command2_Click()
If znum <> 10000 Then
    If Pt(znum).BackColor = 0 Then
        Pt(znum).BackColor = 255
    Else
        Pt(znum).BackColor = 0
    End If
    
    
End If

End Sub

Private Sub Form_Load()
Dim X As Integer
Dim Y As Integer
Dim num As Integer
Pt(0).ToolTipText = "x: 0,y: 0"
For Y = 0 To 35
    For X = 0 To 31
        If X <> 0 Or Y <> 0 Then
            
            num = Y * 32 + X
            Load Pt(num)
            Pt(num).Top = Y * 300
            Pt(num).Left = X * 300
            Pt(num).Height = 300
            Pt(num).Width = 300
            Pt(num).Visible = True
            Pt(num).Enabled = True
            Pt(num).ToolTipText = "x:" + Str(X) + ",y:" + Str(Y)
        End If
    Next
Next

End Sub

Private Sub Pt_MouseDown(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
If Button = 1 Then
    
    If Pt(Index).BackColor = 0 Then
    Pt(Index).BackColor = 255
    Else
    Pt(Index).BackColor = 0
    End If
    znum = Index
End If

If Button = 2 Then
Indexshowpt = Index
PopupMenu Popmenu

End If

End Sub

Private Sub 生成代码_Click()


ShowPt.Visible = True
End Sub
