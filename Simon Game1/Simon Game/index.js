var start=-1;
var level=1;
var userEnter=[];
var generated=[];
var col=["blue","green","red","yellow"];

$("body").on("keypress",function(evt){
    // console.log(evt.key);
  
    if(evt.key=="a" && start<0){
        start=1;
        level=0;
       
        play();
    }
})

$(".btn").on("click",function(){
    // console.log("click"+level); 
    var d = $(this).attr('id');
    // console.log(d);
    userEnter.push(d);
    animate(d);
    addSound(d);
    if(start>0)
        check(userEnter.length-1);
})

function play(){
    console.log("play "+level);
    userEnter=[];
    // generated=[];
    $("#level-title").html("level "+(level+1));
    var c=Math.floor(Math.random()*4);
    // console.log(c);
    generated.push(col[c]);
    addSound(col[c]);
    animate(col[c]);
    // check();
    level++;
    // }
}

function check(lvl){
    if(userEnter[lvl]==generated[lvl]){
        if(userEnter.length==generated.length){
            setTimeout(function () {
                play();
            }, 1000);
        }
    }
    else{
        $("#level-title").text("game over");
        // console.log("game over");
        addSound("wrong");
        $("body").addClass("game-over");
        setTimeout(function(){
            $("body").removeClass("game-over");
        },1000);
        start=-1;
        level=0;
        generated=[];
        $("#level-title").html ("Press A Key to Start");
        // play();
    }
    // return ;
}
function animate(c){
    // console.log(c);
    $("#"+c).addClass("anime");
    setTimeout(function(){
        $("#"+c).removeClass("anime");
    },100);
}
function addSound(c){
    var audio=new Audio("sounds/"+c+".mp3");
    audio.play();
}