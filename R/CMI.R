library(stats)
library(data.table)
library(foreign)

dataset_labeled <- as.data.table(read.arff("synth_multidim_010_000.arff"))

if("id" %in% names(dataset_labeled)){
  dataset_labeled <- dataset_labeled[,!"id", with=F]  
}
if("outlier" %in% names(dataset_labeled)) {
  names(dataset_labeled)[which(names(dataset_labeled)=="outlier")] <- "class"
}
if("yes" %in% levels(dataset_labeled$class)){
  dataset_labeled$class <- as.numeric(dataset_labeled$class == "yes")
}else{
  
  if(is.factor(dataset_labeled$class)){
    dataset_labeled$class <- as.numeric(levels(dataset_labeled$class))[dataset_labeled$class]      
  }
  dataset_labeled[,class:=ifelse(class>0, 1, 0),]
}

hCE <- function(data){
  x <- sort(data)
  tmpSum <- 0
  for(i in (1:(length(x)-1))){
    tmpSum <- tmpSum + ((x[i+1] - x[i]) * (i/length(x)) * log(i/length(x)))
  }
  - tmpSum
}

conditionalhCE <- function(data, referenceDim, conditionalDim, numClusters = 1){
  ce <- 0
  clusters <- kmeans(data[, conditionalDim, with=F], numClusters)
  for(c in 1:numClusters){
    ce <- ce + clusters$size[c]/nrow(data) * hCE(data[[referenceDim]][clusters$cluster==c])
  }  
  ce
}

# conditionalhCE(dt, referenceDim = 4, conditionalDim = c(1,2), numClusters = 10)

CMI <- function(data){
  # sum of hCE
  cmi <- 0
  for(i in 1:ncol(data)){
    cmi <- cmi + hCE(as.vector(data[[i]]))
  }
  # sum of conditional hCE
  for(i in 1:ncol(data)){
    cmi <- cmi - conditionalhCE(dt, referenceDim = i, conditionalDim = 1:i, numClusters = 10)
  }
  cmi
}

subspace <- c(3,1,4,2)

# CMI calculation for sample subspace

# find starting 2-dim projection
initialSubspace <- list(sub = c(), contrast = 0)
for(i in 1:length(subspace)){ # interate over indices of subspace dimensions
  for(j in 1:length(subspace)){
    if(i!=j){
      tmp <- hCE(dt[[ subspace[i] ]]) - conditionalhCE(dt, referenceDim = subspace[i], conditionalDim = subspace[j], numClusters = 10)
      # print(list(sub = c(subspace[i], subspace[j]), contrast = tmp))
      if(tmp > initialSubspace$contrast){
        initialSubspace = list(sub = c(subspace[i], subspace[j]), contrast = tmp)
      }
    }
  }
}
initialSubspace
subspace <- subspace[-which(subspace %in% initialSubspace$sub)]

nextSubspace <- list(sub = c(), contrast = 0) # we only take the best dimension level wise
while(length(subspace) > 0){ # while still dimensions left
  for(i in 1:length(subspace)){
    tmp <- hCE(dt[[ subspace[i] ]]) - conditionalhCE(dt, 
                                                     referenceDim = subspace[i], 
                                                     conditionalDim = initialSubspace$sub, 
                                                     numClusters = 10)
    if(tmp > nextSubspace$contrast){
      nextSubspace = list(sub = c(subspace[i], initialSubspace$sub), contrast = tmp)
    }
  }
  initialSubspace <- nextSubspace # update subspace
  nextSubspace <- list(sub = c(), contrast = 0) # we only take the best dimension level wise
  subspace <- subspace[-which(subspace %in% initialSubspace$sub)] # remove added dimension from remaining dimensions
  
}
initialSubspace$sub



