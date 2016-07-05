library(stats)
library(data.table)
library(foreign)

dataset_labeled <- as.data.table(read.arff("synth_multidim_010_000.arff"))

#print(names(dataset_labeled))

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
  print('------------hceBegin:')
  #print(data)
  x <- sort(data)
  tmpSum <- 0
  for(i in (1:(length(x)-1))){
    tmpSum <- tmpSum + ((x[i+1] - x[i]) * (i/length(x)) * log(i/length(x)))
  }
  - tmpSum
  print('tmpSum:'); print(-tmpSum)
}

conditionalhCE <- function(data, referenceDim, conditionalDim, numClusters = 1){
  ce <- 0
  clusters <- kmeans(data[, conditionalDim, with=F], numClusters)
  print('referenceDim:')
  print(referenceDim)
  print('------------')
  print('conditionalDim:')
  print(conditionalDim)
  print('------------')

  for(c in 1:numClusters){
    # hCE(data) Aufruf fuer alle Cluster: nimmt pro Cl. die Dim.(aus IMportparameter) und Cluster
    # Bed.: doppelte [-Klammer in R?
    #print(clusters)
    print('Clustersize:'); print(clusters$size[c])
    ce <- ce + clusters$size[c]/nrow(data) * hCE(data[[referenceDim]][clusters$cluster==c])
  }
  # print(nrow(data)) => 1000
  print('ce:')
  print(ce)
  print('------------Ende condHCE')
  ce
}

# conditionalhCE(dt, referenceDim = 4, conditionalDim = c(1,2), numClusters = 10)

CMI <- function(dt, subspace){
  totalContrast <- 0

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

  totalContrast <- totalContrast + initialSubspace$contrast
  subspace <- subspace[-which(subspace %in% initialSubspace$sub)]

  nextSubspace <- list(sub = c(), contrast = 0) # we only take the best dimension level wise
  while(length(subspace) > 0){ # while still dimensions left
    for(i in 1:length(subspace)){
      tmp <- hCE(dt[[ subspace[i] ]]) - conditionalhCE(dt,
                                                       referenceDim = subspace[i],
                                                       conditionalDim = initialSubspace$sub,
                                                       numClusters = 10)
      #print(tmp)
      if(tmp > nextSubspace$contrast){
        nextSubspace = list(sub = c(subspace[i], initialSubspace$sub), contrast = tmp)
      }
    }
    totalContrast <- totalContrast + nextSubspace$contrast
    initialSubspace <- nextSubspace # update subspace
    nextSubspace <- list(sub = c(), contrast = 0) # we only take the best dimension level wise
    subspace <- subspace[-which(subspace %in% initialSubspace$sub)] # remove added dimension from remaining dimensions

  }

  totalContrast
}

subspace <- c(3,4,5,6)
dt <- dataset_labeled

CMI(dt, subspace)

# Ausgabe der Clustergroeße (ein Bsp):
#85
#87
#115
#112
#86
#131
#110
#144
#82
#48

# Anzahl Datenpunkte (Summe Clusterpkt) = 1000
# print(nrow(data)) => 1000
